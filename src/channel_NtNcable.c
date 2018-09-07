/*
 * Copyright 2018 Oticon A/S
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "bs_types.h"
#include "p2G4_pending_tx_rx_list.h"
#include "channel_NtNcable_args.h"
#include "channel_if.h"

static uint n_devices;
static ch_NtN_args_t args;

/**
 * Initialize the channel
 */
int channel_init(int argc, char *argv[], uint n_devs){
  n_devices = n_devs;

  channel_NtNcable_argparse(argc, argv, &args);
  return 0;
}

/**
 * Recalculate the fading and path loss of the channel in this current moment (<now>)
 * in between the N used paths and the receive path (<rxnbr>)
 *
 * inputs:
 *  tx_used    : array with n_devs elements, 0: that tx is not transmitting,
 *                                           1: that tx is transmitting,
 *               e.g. {0,1,1,0}: devices 1 and 2 are transmitting, device 0 and 3 are not.
 *  tx_list    : array with all transmissions status (the channel can check here the modulation type of the transmitter if necessary)
 *               (ignored in this channel)
 *  txnbr      : desired transmitter number (the channel will calculate the ISI only for the desired transmitter)
 *               (ignored in this channel)
 *  rxnbr      : device number which is receiving
 *               (ignored in this channel)
 *  now        : current time
 *               (ignored in this channel)
 *  att        : array with n_devs elements. The channel will overwrite the element i
 *               with the average attenuation from path i to rxnbr (in dBs)
 *               The caller allocates this array
 *  ISI_SNR    : The channel will return here an estimate of the SNR limit due to multipath
 *               caused ISI for the desired transmitter (in dBs)
 *               (This channel sets this value always to 100.0)
 *
 * Returns < 0 on error.
 * 0 otherwise
 */
int channel_calc(const uint *tx_used, tx_el_t *tx_list, uint txnbr, uint rxnbr, bs_time_t now, double *att, double *ISI_SNR){
  uint i;
  for ( i = 0 ; i < n_devices; i++ ){
      att[i] = args.attenuation;
  }
  *ISI_SNR = 100;

  return 0;
}

/**
 * Clean up: Free the memory the channel may have allocate
 * close any file descriptors etc.
 * (the simulation has ended)
 */
void channel_delete(){

}
