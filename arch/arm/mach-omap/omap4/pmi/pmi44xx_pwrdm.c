/*
 *
 * @Component			OMAPCONF
 * @Filename			pmi44xx_pwrdm.c
 * @Description			OMAP4 PMI Power Domain Transition Trace
 *				Decoding library
 * @Author			Patrick Titiano (p-titiano@ti.com)
 * @Date			2011
 * @Copyright			Texas Instruments Incorporated
 *
 *
 * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */


#include <pmi44xx_pwrdm.h>
#include <stdio.h>
#include <autoadjust_table.h>
#include <lib44xx.h>
#include <dpll.h>
#include <dpll44xx.h>
#include <stm44xx.h>
#include <clock44xx.h>
#include <lib.h>
#include <cpuinfo.h>
#include <string.h>


/* #define PMI_PWRDM_OMAP4_DEBUG */
#ifdef PMI_PWRDM_OMAP4_DEBUG
	#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#else
	#define dprintf(format, ...)
#endif


typedef struct {
	pmi_event_class class;
	unsigned int pm_states_msb;
	unsigned int pm_states_lsb;
	double ts; /* relative, in micro-seconds */
} pwrdm_event;


/* #define PMI_PWRDM_TRANSITIONS_FIND_DEBUG */
#ifdef PMI_PWRDM_TRANSITIONS_FIND_DEBUG
#undef dprintf
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#endif
/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pmi_pwrdm_transitions_find
 * @BRIEF		find power domain transition(s) in list of PMI pm events
 * @RETURNS		>=0 total number of power domain transitions found
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_UNEXPECTED
 * @param[in,out]	pm_events: list of pm events retrieved from PMI trace.
 * @param[in]		duration: trace duration in microseconds.
 * @param[in]		transitions: list of power transition(s) for each domain
 * @DESCRIPTION		find power domain transition(s) in list of PMI pm events
 *//*------------------------------------------------------------------------ */
int pmi_pwrdm_transitions_find(genlist *pm_events,
	double duration, pwrdm_transitions transitions)
{
	unsigned int pm_states, shift, pos;
	pwrdm_state pwrdm_st, curr_pwrdm_st = PWRDM_OFF_STATE;
	pwrdm_transition tr;
	char pwrdm_state_s[6] = { 0 };
	#ifdef PMI_PWRDM_TRANSITIONS_FIND_DEBUG
	char *name;
	#endif
	int pm_evt_count, evt;
	unsigned int dom;
	pwrdm_event event;
	pmi_event_class class;
	double ts_last_change, time;
	unsigned int first_state;
	unsigned int pwr_trans_count;

	if (pm_events == NULL) {
		printf("pmi_pwrdm_transitions_find() error: "
			"pm_events == NULL!\n");
		return OMAPCONF_ERR_ARG;
	}
	if (duration == 0.0) {
		printf("pmi_pwrdm_transitions_get() error: "
			"duration == 0.0!\n");
		return OMAPCONF_ERR_ARG;
	}
	if (transitions == NULL) {
		printf("pmi_pwrdm_transitions_find() error: "
			"transitions == NULL!\n");
		return OMAPCONF_ERR_ARG;
	}

	/* Get number of pm events */
	pm_evt_count = genlist_getcount(pm_events);
	if (pm_evt_count < 0) {
		printf("pmi_pwrdm_transitions_find(): incorrect event list!\n");
		return OMAPCONF_ERR_ARG;
	} else if (pm_evt_count == 0) {
		dprintf("pmi_pwrdm_transitions_find(): empty event list.\n");
		return 0;
	}

	/*
	 * For each domain (logic and memory), go through pm events list
	 * and detect changes. In case of state change, save it into the
	 * corresponding list.
	 */
	dprintf("pmi_pwrdm_transitions_find(): start browsing "
		"domains and events ...\n");
	pwr_trans_count = 0;
	for (dom = 0; dom < OMAP4_PMI_PWRDM_MAX; dom++) {
		/* Init list */
		genlist_init(&(transitions[dom]));

		/* Get domain class */
		if (dom < OMAP4_PMI_LOGIC_PWRDM_MAX) {
			class = PMI_PWRDM_CLASS_LOGIC;
			pos = dom;
			#ifdef PMI_PWRDM_TRANSITIONS_FIND_DEBUG
			name = (char *) omap4_pmi_logic_pwrdm_names_table[pos];
			#endif
		} else {
			class = PMI_PWRDM_CLASS_MEM;
			pos = dom - OMAP4_PMI_LOGIC_PWRDM_MAX;
			#ifdef PMI_PWRDM_TRANSITIONS_FIND_DEBUG
			name = (char *) omap4_pmi_mem_pwrdm_names_table[pos];
			#endif
		}
		dprintf("\n------------- %s ------------\n", name);

		ts_last_change = 0.0;
		time = 0.0;
		first_state = 1;
		for (evt = 0; evt < pm_evt_count; evt++) {
			dprintf("PM event #%d\n", evt);
			/* Get pm event */
			genlist_get(pm_events,
				pm_evt_count - 1 - evt, &event);
			dprintf("\tevent.pm_states_lsb =0x%08X\n",
				event.pm_states_lsb);
			if (event.class == PMI_PWRDM_CLASS_MEM) {
				dprintf("\tevent.pm_states_msb =0x%08X\n",
					event.pm_states_msb);
			}
			dprintf("\tevent.class=%d\n", event.class);
			dprintf("\tevent.ts=%lfus\n", event.ts);
			time += (double) event.ts;
			dprintf("Time is %lfus\n", time);
			if (event.class != class) {
				dprintf("PM Event Class is not the same "
					"(%d instead of %d)\n",
					event.class, class);
				continue;
			}

			/* Extract domain power state */
			if (class == PMI_PWRDM_CLASS_LOGIC) {
				pm_states = event.pm_states_lsb;
				pos = dom;
				shift = 2 * (15 - pos);
			} else { /* class == PMI_PWRDM_CLASS_MEM */
				pos = dom - OMAP4_PMI_LOGIC_PWRDM_MAX;
				if ((dom - OMAP4_PMI_LOGIC_PWRDM_MAX) < 16) {
					pm_states = event.pm_states_msb;
					shift = 2 * (15 - pos);
				} else {
					pm_states = event.pm_states_lsb;
					shift = 2 * (31 - pos);
				}
			}
			pwrdm_st = (pwrdm_state)
				((pm_states & (3 << shift)) >> shift);
			dprintf("pos=%d, shift=%d, pm_states=0x%08X, "
				"pwrdm_st=%d\n",
				pos, shift, pm_states, pwrdm_st);
			if (pwrdm_st >= PWRDM_STATE_MAX) {
				printf("pmi_pwrdm_transitions_find() error: "
					"incorrect state! (%d)\n", pwrdm_st);
				return OMAPCONF_ERR_UNEXPECTED;
			}
			pwrdm_state2string(pwrdm_state_s, pwrdm_st);

			if (first_state) {
				curr_pwrdm_st = pwrdm_st;
				first_state = 0;
				dprintf("Domain first state is %s (%d)\n",
					pwrdm_state_s, pwrdm_st);
				continue;
			}

			if (pwrdm_st != curr_pwrdm_st) {
				/* Store state in corresponding list */
				tr.class = class;
				tr.id = dom;
				tr.state = curr_pwrdm_st;
				tr.ts = time - event.ts - ts_last_change;
				pwrdm_state2string(pwrdm_state_s,
					tr.state);
				dprintf("Domain stayed %s (%d) during %lfus\n",
					pwrdm_state_s, tr.state, tr.ts);
				genlist_addtail(&(transitions[dom]),
						&tr, sizeof(pwrdm_transition));
				curr_pwrdm_st = pwrdm_st;
				ts_last_change = time - event.ts;
				pwrdm_state2string(pwrdm_state_s,
					curr_pwrdm_st);
				dprintf("Domain new state = %s (%d) at %lfus\n",
					pwrdm_state_s, curr_pwrdm_st,
					time - event.ts);
				pwr_trans_count++;
			}
		}
		if (ts_last_change != time) {
			/* This is the last event and state didn't change */
			/* Store state in corresponding list */
			tr.class = class;
			tr.id = dom;
			tr.state = curr_pwrdm_st;
			tr.ts = time - ts_last_change;
			pwrdm_state2string(pwrdm_state_s, tr.state);
			dprintf("Domain stayed %s (%d) during %lfus "
				"until the end of the trace\n",
				pwrdm_state_s, tr.state, tr.ts);
			genlist_addtail(&(transitions[dom]),
					&tr, sizeof(pwrdm_transition));
			pwr_trans_count++;
		}
		dprintf("--------------------------------------------\n");
	}
	dprintf("pmi_pwrdm_transitions_find(): found %d power transitions\n",
		pwr_trans_count);

	return pwr_trans_count;
}
#ifdef PMI_PWRDM_TRANSITIONS_FIND_DEBUG
#undef dprintf
#define dprintf(format, ...)
#endif


/* #define PMI_PWRDM_EVENTS_GET_DEBUG */
#ifdef PMI_PWRDM_EVENTS_GET_DEBUG
#undef dprintf
#define dprintf(format, ...)	 printf(format, ## __VA_ARGS__)
#endif
/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pmi_pwrdm_events_get
 * @BRIEF		retrieve PM event(s) from PMI trace file.
 * @RETURNS		>=0 total number of PM events extracted from PMI trace
 *			file.
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_UNEXPECTED
 * @param[in,out]	filename: PMI trace file generated by
 *				pmi_pwrdm_trace_decode
 * @param[in,out]	pm_events: list of PM events extracted from PMI
 *				trace file
 * @DESCRIPTION		retrieve PM event(s) from PMI trace file.
 *//*------------------------------------------------------------------------ */
int pmi_pwrdm_events_get(char *filename, genlist *pm_events)
{
	double ts;
	unsigned int pm_class, pm_state_lsb, pm_state_msb;
	FILE *fp;
	char line[256];
	char dummy[7];
	pwrdm_event evt;
	unsigned int pm_events_count;

	if (pm_events == NULL) {
		printf("pmi_pwrdm_events_get() error: "
			"pm_events == NULL!\n");
		return OMAPCONF_ERR_ARG;
	}
	if (filename == NULL) {
		printf("pmi_pwrdm_events_get() error: "
			"filename == NULL!\n");
		return OMAPCONF_ERR_ARG;
	}

	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("pmi_pwrdm_events_get() error: "
			"could not open %s!\n", filename);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	genlist_init(pm_events);
	pm_events_count = 0;

	dprintf("pmi_pwrdm_events_get(): "
		"parsing trace file...\n");
	while (fgets(line, sizeof(line), fp) != NULL) {
		/* Looking for D8 headers */
		if (strstr(line, "D8 (0x4)") == NULL)
			continue;

		dprintf("new D8 found\n");
		/* Retrieve PM Class */
		if (fgets(line, sizeof(line), fp) == NULL) {
			printf("unexpected end of line reached!\n");
			fclose(fp);
			return OMAPCONF_ERR_UNEXPECTED;
		}
		if (sscanf(line, "\tEvent Class is %s Power Domain (0x%02X)",
			dummy, &pm_class) != 2) {
			printf("could not get class from %s", line);
			fclose(fp);
			return OMAPCONF_ERR_UNEXPECTED;
		}
		if (pm_class == PMI_PWRDM_CLASS_LOGIC) {
			dprintf("pm class is %d (LOGIC)\n", pm_class);
		} else if (pm_class == PMI_PWRDM_CLASS_MEM) {
			dprintf("pm class is %d (MEM)\n", pm_class);
		} else {
			printf("unexpected pm class found! (%d)\n", pm_class);
			fclose(fp);
		}
		evt.class = (pmi_event_class) pm_class;

		/* Retrieve PM state */
		if (fgets(line, sizeof(line), fp) == NULL) {
			printf("unexpected end of line reached!\n");
			fclose(fp);
			return OMAPCONF_ERR_UNEXPECTED;
		}
		if (pm_class == PMI_PWRDM_CLASS_LOGIC) {
			if (sscanf(line, "\t\tEvent Data = 0x%08X",
				&pm_state_lsb) != 1) {
				printf("could not get state from %s", line);
				fclose(fp);
				return OMAPCONF_ERR_UNEXPECTED;
			}
			dprintf("pm state is 0x%08X\n", pm_state_lsb);
			pm_state_msb = 0;
		} else {
			if (sscanf(line, "\t\tEvent Data = 0x%08X%08X",
				&pm_state_msb, &pm_state_lsb) != 2) {
				printf("could not get state from %s", line);
				fclose(fp);
				return OMAPCONF_ERR_UNEXPECTED;
			}
			dprintf("pm state is 0x%08X%08X\n",
				pm_state_msb, pm_state_lsb);
		}
		evt.pm_states_lsb = pm_state_lsb;
		evt.pm_states_msb = pm_state_msb;
		genlist_addtail(pm_events, &evt, sizeof(pwrdm_event));
		pm_events_count++;

		/* Retrieve relative timestamp from next line */
		if (fgets(line, sizeof(line), fp) == NULL) {
			printf("unexpected end of line reached!\n");
			fclose(fp);
			return OMAPCONF_ERR_UNEXPECTED;
		}
		if (sscanf(line, "\tTimestamp (relative) = %lfus", &ts) != 1) {
			printf("could not get timestamp from %s", line);
			fclose(fp);
			return OMAPCONF_ERR_UNEXPECTED;
		}
		dprintf("timestamp is %lfus\n", ts);
		evt.ts = ts;
	}
	fclose(fp);
	dprintf("pmi_pwrdm_events_get(): found %d pm events.\n",
		pm_events_count);

	return pm_events_count;
}
#ifdef PMI_PWRDM_EVENTS_GET_DEBUG
#undef dprintf
#define dprintf(format, ...)
#endif


/* ------------------------------------------------------------------------*//**
 * @FUNCTION		pmi_pwrdm_transitions_save
 * @BRIEF		save power domain transitions it into file.
 * @RETURNS		0 in case of success
 *			OMAPCONF_ERR_ARG
 *			OMAPCONF_ERR_NOT_AVAILABLE
 *			OMAPCONF_ERR_UNEXPECTED
 * @param[in,out]	filename: name of the file where to save power
 *				transitions
 * @param[in]		transitions: list of power transitions for each domains
 * @param[in]		duration: total trace duration in microseconds.
 * @DESCRIPTION		save power domain transitions it into file.
 *//*------------------------------------------------------------------------ */
int pmi_pwrdm_transitions_save(char *filename,
	pwrdm_transitions transitions, double duration)
{
	unsigned int i, dom;
	pwrdm_transition tr;
	int count, evt;
	char *name;
	char s[6];
	FILE *fp = NULL;

	if (transitions == NULL) {
		printf("pmi_pwrdm_transitions_save(): "
			"transitions == NULL!\n");
		return OMAPCONF_ERR_ARG;
	}
	if (filename == NULL) {
		printf("pmi_pwrdm_transitions_save(): "
			"filename == NULL!\n");
		return OMAPCONF_ERR_ARG;
	}

	fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("pmi_pwrdm_transitions_save() error: "
			"could not create %s!\n", filename);
		return OMAPCONF_ERR_NOT_AVAILABLE;
	}

	fprintf(fp, "OMAP4430 Power Domain Transitions Log\n\n");
	fprintf(fp, "---------- Trace DURATION ----------\n");
	fprintf(fp, "%lf, unit = us\n", duration);
	fprintf(fp, "---------- Trace FORMAT ----------\n");
	fprintf(fp, "Domain Name\n");
	fprintf(fp, "Timestamp (in micro-seconds), "
		"Domain State (decimal value), Domain State Name (string)\n");
	fprintf(fp, "---------- Trace START ----------\n");
	for (i = 0; i < OMAP4_USED_PMI_PWRDMS; i++) {
		dom = sorted_domain_ids[i];

		/*
		 * OMAP4 WORKAROUND:
		 * HW bug in OMAP4 makes CPU[0-1] trace irrelevant ...
		 * => Skip these domains ...
		 */
		if (((sorted_domain_class[i] == PMI_PWRDM_CLASS_LOGIC) &&
				(dom == OMAP4_PMI_LOGIC_PWRDM_A9_C1)) ||
			((sorted_domain_class[i] == PMI_PWRDM_CLASS_LOGIC) &&
				(dom == OMAP4_PMI_LOGIC_PWRDM_A9_C0)) ||
			((sorted_domain_class[i] == PMI_PWRDM_CLASS_MEM) &&
				(dom == OMAP4_PMI_MEM_PWRDM_MPU_M1)) ||
			((sorted_domain_class[i] == PMI_PWRDM_CLASS_MEM) &&
				(dom == OMAP4_PMI_MEM_PWRDM_MPU_M0)))
			continue;

		if (sorted_domain_class[i] == PMI_PWRDM_CLASS_LOGIC) {
			name = (char *) omap4_pmi_logic_pwrdm_names_table[dom];
		} else {
			name = (char *) omap4_pmi_mem_pwrdm_names_table[dom];
			dom += OMAP4_PMI_LOGIC_PWRDM_MAX;
		}

		fprintf(fp, "%s\n", name);
		if (genlist_isempty(&(transitions[dom])) == 1) {
			printf("List %d (%s) should not be empty!!!\n",
				dom , name);
			fclose(fp);
			return OMAPCONF_ERR_UNEXPECTED;
		}

		/* First element in list is the initial state */
		count = genlist_getcount(&(transitions[dom]));
		for (evt = 0; evt < count; evt++) {
			genlist_get(&(transitions[dom]), evt, &tr);
			pwrdm_state2string(s, tr.state);
			fprintf(fp, "%lf,%d,%s\n", tr.ts, tr.state, s);
		}
	}
	fprintf(fp, "---------- Trace END ----------\n");
	fclose(fp);

	return 0;
}
