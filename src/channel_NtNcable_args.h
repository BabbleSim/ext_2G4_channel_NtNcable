/*
 * Copyright 2018 Oticon A/S
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef BS_CHANNEL_NTN_CABLE_ARGS_H
#define BS_CHANNEL_NTN_CABLE_ARGS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct{
  double attenuation;
} ch_NtN_args_t;

void channel_NtNcable_argparse(int argc, char *argv[], ch_NtN_args_t *args);

#ifdef __cplusplus
}
#endif

#endif
