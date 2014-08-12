/*
 * sci_common.h
 *
 * Statistic Collector Instrumentation Library
 * - Statistic Collector module specific definitions
 * - Device specific configurations
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

#ifndef SCI_COMMON_H
#define SCI_COMMON_H

#include <stdlib.h>
#include <stdint.h>
#include "sc_reg.h"

/* Statistic Collector register typedef */


/*
 * Register definitions
 *
 */
#define SC_REQUEST_PROBE        0x0
#define SC_RESPONSE_PROBE       0x1


#define SC_EVENT_SEL_NONE     0x0 /* No event selected */
#define SC_EVENT_SEL_ANY      0x1 /* Any clock cycles */
#define SC_EVENT_SEL_TRANSFER 0x2 /* Header, necker or data has been accepted by the receiver */
#define SC_EVENT_SEL_WAIT     0x3 /* Transfer initiated but the transmitter has no data to send */
#define SC_EVENT_SEL_BUSY     0x4 /* Receiver applies flow control */
#define SC_EVENT_SEL_PKT      0x5 /* Transfer of a new packet header */
#define SC_EVENT_SEL_DATA     0x6 /* Transfer of a payload word
                                     *   Request link: Store data
                                     *   Respose link: Load data
                                     */
#define SC_EVENT_SEL_IDLE     0x7 /* No communication over the link */
#define SC_EVENT_SEL_LATENCY  0x8 /* Debug bit detection */

/* If op_sel set to MIN_MAX_HIT or EVT_INFO then evt_info_sel applies */
#define SC_EVTINFOSEL_BYTELEN   0x0 /* Length of transfer in bytes */
#define SC_EVTINFOSEL_PRESSURE  0x1 /* Pressure */
#define SC_EVTINFOSEL_LATENCY   0x2 /* Amount of wait time */

/* op_sel determines how the counter functions */
#define SC_OPSEL_FILTER_HIT     0x0 /* Counter increments on a filter hit */
#define SC_OPSEL_MINMAX_HIT     0x1 /* Counter increments when the filter hits
                                     * and the selected event info is in range
                                     * (Min threshold <= Evt_Info <= Max threshold)
                                     */
#define SC_OPSEL_EVT_INFO       0x2 /* Selected Evt_Info added to the counter value
                                     * when the filter hits
                                     */
#define SC_OPSEL_AND_FILTER     0x3 /* Counter increments by one when all unit
                                     * filters hit.
                                     */
#define SC_OPSEL_OR_FILTER      0x4 /* Counter increments by one when at least
                                     * one unit filters hits.
                                     */
#define SC_OPSEL_SUM_REQ_EVT    0x5 /* Counter sums the events from any request
                                     * port.
                                     */
#define SC_OPSEL_SUM_RSP_EVT    0x6 /* Counter sums the events from any response
                                     * port.
                                     */
#define SC_OPSEL_SUM_ALL_EVT    0x7 /* Counter sums the events from any request
                                     * and response ports.
                                     */
#define SC_OPSEL_EX_EVT         0x8 /* Counter increments by one when the selected
                                     * ExtEvt input signal is sampled high
                                     */
#define SC_GET_USECASE_COMPAT_VALUE(n) ((n) >> 16)
#define SC_USECASE_MASK(n)             ((n) & 0x000000FF)

#define SC_MOD_TYPE (0x003A0001)     /* Identifies the module as a SC Module */

#define GET_SCMOD_FUNC(n) ((n) >> 24)

#define DMM_LISA_MAP_BASE 0x4e000040
typedef union DMM_LISA_MAP
{
    unsigned int val;
    struct {
        unsigned int sdrc_addr   :8;
        unsigned int sdrc_map    :2;
        unsigned int             :6;
        unsigned int sdrc_addrspc:2;
        unsigned int sdrc_intl   :2;
        unsigned int sys_size    :3;
        unsigned int             :1;
        unsigned int sys_addr    :8;
    } field;
}DMM_LISA_MAP;

#endif
/* End of SCI_COMMON_H */
