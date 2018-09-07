/*
 * Copyright 2018 Oticon A/S
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "channel_NtNcable_args.h"
#include "bs_tracing.h"
#include "bs_oswrap.h"
#include "bs_cmd_line_typical.h"

static char library_name[] = "Channel N to N cable";

void component_print_post_help() {
  fprintf(stdout,"This is a non realistic channel,\n"
      "It will mix all N inputs together and pass them to all N outputs with a given\n"
      "attenuation. If attenuation is set to 0, the full Tx power will go to all\n"
      "inputs\n\n");
}

ch_NtN_args_t *args_g;

void cmd_att_found(char * argv, int offset) {
  if ((args_g->attenuation < -100) || (args_g->attenuation > 100)) {
    bs_trace_error("channel: cmdarg: attenuation can only be between -100 and 100dB (%lf)\n", args_g->attenuation);
  }
}

/**
 * Check the arguments provided in the command line: set args based on it
 * or defaults, and check they are correct
 */
void channel_NtNcable_argparse(int argc, char *argv[], ch_NtN_args_t *args) {
  args_g = args;
  bs_args_struct_t args_struct[] = {
    /*manual,mandatory,switch,option,   name ,     type,   destination,               callback,      , description*/
    { false , false  , false, "at", "attenuation", 'f', (void*)&args->attenuation, cmd_att_found, "attenuation in dB, used in all NxN paths (can be be <0) Default: 60dB"},
    ARG_TABLE_ENDMARKER
  };

  args->attenuation = 60;

  char trace_prefix[50]; //it will not be used as soon as we get out of this function
  snprintf(trace_prefix,50, "channel: (NtNcable) ");

  bs_args_override_exe_name(library_name);
  bs_args_set_trace_prefix(trace_prefix);
  bs_args_parse_all_cmd_line(argc, argv, args_struct);
}
