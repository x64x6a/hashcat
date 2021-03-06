/**
 * Author......: See docs/credits.txt
 * License.....: MIT
 */

#include "common.h"
#include "types.h"
#include "memory.h"
#include "event.h"
#include "logfile.h"
#include "interface.h"
#include "shared.h"
#include "usage.h"
#include "outfile.h"
#include "user_options.h"

static const char short_options[] = "hVvm:a:r:j:k:g:o:t:d:D:n:u:c:p:s:l:1:2:3:4:iIbw:";

static const struct option long_options[] =
{
  {"attack-mode",               required_argument, 0, IDX_ATTACK_MODE},
  {"benchmark",                 no_argument,       0, IDX_BENCHMARK},
  {"bitmap-max",                required_argument, 0, IDX_BITMAP_MAX},
  {"bitmap-min",                required_argument, 0, IDX_BITMAP_MIN},
  {"cpu-affinity",              required_argument, 0, IDX_CPU_AFFINITY},
  {"custom-charset1",           required_argument, 0, IDX_CUSTOM_CHARSET_1},
  {"custom-charset2",           required_argument, 0, IDX_CUSTOM_CHARSET_2},
  {"custom-charset3",           required_argument, 0, IDX_CUSTOM_CHARSET_3},
  {"custom-charset4",           required_argument, 0, IDX_CUSTOM_CHARSET_4},
  {"debug-file",                required_argument, 0, IDX_DEBUG_FILE},
  {"debug-mode",                required_argument, 0, IDX_DEBUG_MODE},
  {"force",                     no_argument,       0, IDX_FORCE},
  {"generate-rules-func-max",   required_argument, 0, IDX_RP_GEN_FUNC_MAX},
  {"generate-rules-func-min",   required_argument, 0, IDX_RP_GEN_FUNC_MIN},
  {"generate-rules",            required_argument, 0, IDX_RP_GEN},
  {"generate-rules-seed",       required_argument, 0, IDX_RP_GEN_SEED},
  {"gpu-temp-abort",            required_argument, 0, IDX_GPU_TEMP_ABORT},
  {"gpu-temp-disable",          no_argument,       0, IDX_GPU_TEMP_DISABLE},
  {"gpu-temp-retain",           required_argument, 0, IDX_GPU_TEMP_RETAIN},
  {"hash-type",                 required_argument, 0, IDX_HASH_MODE},
  {"help",                      no_argument,       0, IDX_HELP},
  {"hex-charset",               no_argument,       0, IDX_HEX_CHARSET},
  {"hex-salt",                  no_argument,       0, IDX_HEX_SALT},
  {"hex-wordlist",              no_argument,       0, IDX_HEX_WORDLIST},
  {"increment-max",             required_argument, 0, IDX_INCREMENT_MAX},
  {"increment-min",             required_argument, 0, IDX_INCREMENT_MIN},
  {"increment",                 no_argument,       0, IDX_INCREMENT},
  {"induction-dir",             required_argument, 0, IDX_INDUCTION_DIR},
  {"keep-guessing",             no_argument,       0, IDX_KEEP_GUESSING},
  {"kernel-accel",              required_argument, 0, IDX_KERNEL_ACCEL},
  {"kernel-loops",              required_argument, 0, IDX_KERNEL_LOOPS},
  {"keyspace",                  no_argument,       0, IDX_KEYSPACE},
  {"left",                      no_argument,       0, IDX_LEFT},
  {"limit",                     required_argument, 0, IDX_LIMIT},
  {"logfile-disable",           no_argument,       0, IDX_LOGFILE_DISABLE},
  {"loopback",                  no_argument,       0, IDX_LOOPBACK},
  {"machine-readable",          no_argument,       0, IDX_MACHINE_READABLE},
  {"markov-classic",            no_argument,       0, IDX_MARKOV_CLASSIC},
  {"markov-disable",            no_argument,       0, IDX_MARKOV_DISABLE},
  {"markov-hcstat",             required_argument, 0, IDX_MARKOV_HCSTAT},
  {"markov-threshold",          required_argument, 0, IDX_MARKOV_THRESHOLD},
  {"nvidia-spin-damp",          required_argument, 0, IDX_NVIDIA_SPIN_DAMP},
  {"opencl-devices",            required_argument, 0, IDX_OPENCL_DEVICES},
  {"opencl-device-types",       required_argument, 0, IDX_OPENCL_DEVICE_TYPES},
  {"opencl-info",               no_argument,       0, IDX_OPENCL_INFO},
  {"opencl-platforms",          required_argument, 0, IDX_OPENCL_PLATFORMS},
  {"opencl-vector-width",       required_argument, 0, IDX_OPENCL_VECTOR_WIDTH},
  {"outfile-autohex-disable",   no_argument,       0, IDX_OUTFILE_AUTOHEX_DISABLE},
  {"outfile-check-dir",         required_argument, 0, IDX_OUTFILE_CHECK_DIR},
  {"outfile-check-timer",       required_argument, 0, IDX_OUTFILE_CHECK_TIMER},
  {"outfile-format",            required_argument, 0, IDX_OUTFILE_FORMAT},
  {"outfile",                   required_argument, 0, IDX_OUTFILE},
  {"potfile-disable",           no_argument,       0, IDX_POTFILE_DISABLE},
  {"potfile-path",              required_argument, 0, IDX_POTFILE_PATH},
  {"powertune-enable",          no_argument,       0, IDX_POWERTUNE_ENABLE},
  {"quiet",                     no_argument,       0, IDX_QUIET},
  {"remove",                    no_argument,       0, IDX_REMOVE},
  {"remove-timer",              required_argument, 0, IDX_REMOVE_TIMER},
  {"restore-disable",           no_argument,       0, IDX_RESTORE_DISABLE},
  {"restore-file-path",         required_argument, 0, IDX_RESTORE_FILE_PATH},
  {"restore",                   no_argument,       0, IDX_RESTORE},
  {"rule-left",                 required_argument, 0, IDX_RULE_BUF_L},
  {"rule-right",                required_argument, 0, IDX_RULE_BUF_R},
  {"rules-file",                required_argument, 0, IDX_RP_FILE},
  {"runtime",                   required_argument, 0, IDX_RUNTIME},
  {"scrypt-tmto",               required_argument, 0, IDX_SCRYPT_TMTO},
  {"segment-size",              required_argument, 0, IDX_SEGMENT_SIZE},
  {"separator",                 required_argument, 0, IDX_SEPARATOR},
  {"seperator",                 required_argument, 0, IDX_SEPARATOR},
  {"session",                   required_argument, 0, IDX_SESSION},
  {"show",                      no_argument,       0, IDX_SHOW},
  {"skip",                      required_argument, 0, IDX_SKIP},
  {"status",                    no_argument,       0, IDX_STATUS},
  {"status-timer",              required_argument, 0, IDX_STATUS_TIMER},
  {"stdout",                    no_argument,       0, IDX_STDOUT_FLAG},
  {"speed-only",                no_argument,       0, IDX_SPEED_ONLY},
  {"truecrypt-keyfiles",        required_argument, 0, IDX_TRUECRYPT_KEYFILES},
  {"username",                  no_argument,       0, IDX_USERNAME},
  {"veracrypt-keyfiles",        required_argument, 0, IDX_VERACRYPT_KEYFILES},
  {"veracrypt-pim",             required_argument, 0, IDX_VERACRYPT_PIM},
  {"version",                   no_argument,       0, IDX_VERSION},
  {"weak-hash-threshold",       required_argument, 0, IDX_WEAK_HASH_THRESHOLD},
  {"workload-profile",          required_argument, 0, IDX_WORKLOAD_PROFILE},
  {0, 0, 0, 0}
};

static char RULE_BUF_R[] = ":";
static char RULE_BUF_L[] = ":";

static char DEF_MASK_CS_1[] = "?l?d?u";
static char DEF_MASK_CS_2[] = "?l?d";
static char DEF_MASK_CS_3[] = "?l?d*!$@_";

int user_options_init (hashcat_ctx_t *hashcat_ctx)
{
  user_options_t *user_options = hashcat_ctx->user_options;

  user_options->attack_mode               = ATTACK_MODE;
  user_options->benchmark                 = BENCHMARK;
  user_options->bitmap_max                = BITMAP_MAX;
  user_options->bitmap_min                = BITMAP_MIN;
  user_options->cpu_affinity              = NULL;
  user_options->custom_charset_1          = NULL;
  user_options->custom_charset_2          = NULL;
  user_options->custom_charset_3          = NULL;
  user_options->custom_charset_4          = NULL;
  user_options->debug_file                = NULL;
  user_options->debug_mode                = DEBUG_MODE;
  user_options->force                     = FORCE;
  user_options->gpu_temp_abort            = GPU_TEMP_ABORT;
  user_options->gpu_temp_disable          = GPU_TEMP_DISABLE;
  user_options->gpu_temp_retain           = GPU_TEMP_RETAIN;
  user_options->hash_mode                 = HASH_MODE;
  user_options->hex_charset               = HEX_CHARSET;
  user_options->hex_salt                  = HEX_SALT;
  user_options->hex_wordlist              = HEX_WORDLIST;
  user_options->increment                 = INCREMENT;
  user_options->increment_max             = INCREMENT_MAX;
  user_options->increment_min             = INCREMENT_MIN;
  user_options->induction_dir             = NULL;
  user_options->kernel_accel              = KERNEL_ACCEL;
  user_options->kernel_loops              = KERNEL_LOOPS;
  user_options->keep_guessing             = KEEP_GUESSING;
  user_options->keyspace                  = KEYSPACE;
  user_options->left                      = LEFT;
  user_options->limit                     = LIMIT;
  user_options->logfile_disable           = LOGFILE_DISABLE;
  user_options->loopback                  = LOOPBACK;
  user_options->machine_readable          = MACHINE_READABLE;
  user_options->markov_classic            = MARKOV_CLASSIC;
  user_options->markov_disable            = MARKOV_DISABLE;
  user_options->markov_hcstat             = NULL;
  user_options->markov_threshold          = MARKOV_THRESHOLD;
  user_options->nvidia_spin_damp          = NVIDIA_SPIN_DAMP;
  user_options->opencl_devices            = NULL;
  user_options->opencl_device_types       = NULL;
  user_options->opencl_info               = 0;
  user_options->opencl_platforms          = NULL;
  user_options->opencl_vector_width       = OPENCL_VECTOR_WIDTH;
  user_options->outfile_autohex           = OUTFILE_AUTOHEX;
  user_options->outfile_check_dir         = NULL;
  user_options->outfile_check_timer       = OUTFILE_CHECK_TIMER;
  user_options->outfile_format            = OUTFILE_FORMAT;
  user_options->outfile                   = NULL;
  user_options->potfile_disable           = POTFILE_DISABLE;
  user_options->potfile_path              = NULL;
  user_options->powertune_enable          = POWERTUNE_ENABLE;
  user_options->quiet                     = QUIET;
  user_options->remove                    = REMOVE;
  user_options->remove_timer              = REMOVE_TIMER;
  user_options->restore_disable           = RESTORE_DISABLE;
  user_options->restore_file_path         = NULL;
  user_options->restore                   = RESTORE;
  user_options->restore_timer             = RESTORE_TIMER;
  user_options->rp_gen_func_max           = RP_GEN_FUNC_MAX;
  user_options->rp_gen_func_min           = RP_GEN_FUNC_MIN;
  user_options->rp_gen                    = RP_GEN;
  user_options->rp_gen_seed               = RP_GEN_SEED;
  user_options->rule_buf_l                = RULE_BUF_L;
  user_options->rule_buf_r                = RULE_BUF_R;
  user_options->runtime                   = RUNTIME;
  user_options->scrypt_tmto               = SCRYPT_TMTO;
  user_options->segment_size              = SEGMENT_SIZE;
  user_options->separator                 = SEPARATOR;
  user_options->session                   = PROGNAME;
  user_options->show                      = SHOW;
  user_options->skip                      = SKIP;
  user_options->status                    = STATUS;
  user_options->status_timer              = STATUS_TIMER;
  user_options->stdout_flag               = STDOUT_FLAG;
  user_options->speed_only                = SPEED_ONLY;
  user_options->truecrypt_keyfiles        = NULL;
  user_options->usage                     = USAGE;
  user_options->username                  = USERNAME;
  user_options->veracrypt_keyfiles        = NULL;
  user_options->veracrypt_pim             = 0;
  user_options->version                   = VERSION;
  user_options->weak_hash_threshold       = WEAK_HASH_THRESHOLD;
  user_options->workload_profile          = WORKLOAD_PROFILE;
  user_options->rp_files_cnt              = 0;
  user_options->rp_files                  = (char **) hccalloc (hashcat_ctx, 256, sizeof (char *)); VERIFY_PTR (user_options->rp_files);
  user_options->hc_bin                    = PROGNAME;
  user_options->hc_argc                   = 0;
  user_options->hc_argv                   = NULL;

  return 0;
}

void user_options_destroy (hashcat_ctx_t *hashcat_ctx)
{
  user_options_t *user_options = hashcat_ctx->user_options;

  hcfree (user_options->rp_files);

  //do not reset this, it might be used from main.c
  //memset (user_options, 0, sizeof (user_options_t));
}

int user_options_getopt (hashcat_ctx_t *hashcat_ctx, int argc, char **argv)
{
  user_options_t *user_options = hashcat_ctx->user_options;

  int c = -1;

  optind = 1;
  optopt = 0;

  int option_index = 0;

  while (((c = getopt_long (argc, argv, short_options, long_options, &option_index)) != -1) && optopt == 0)
  {
    switch (c)
    {
      case IDX_HELP:                      user_options->usage                     = true;           break;
      case IDX_VERSION:                   user_options->version                   = true;           break;
      case IDX_RESTORE:                   user_options->restore                   = true;           break;
      case IDX_QUIET:                     user_options->quiet                     = true;           break;
      case IDX_SHOW:                      user_options->show                      = true;           break;
      case IDX_LEFT:                      user_options->left                      = true;           break;
      case IDX_USERNAME:                  user_options->username                  = true;           break;
      case IDX_REMOVE:                    user_options->remove                    = true;           break;
      case IDX_REMOVE_TIMER:              user_options->remove_timer              = atoi (optarg);
                                          user_options->remove_timer_chgd         = true;           break;
      case IDX_POTFILE_DISABLE:           user_options->potfile_disable           = true;           break;
      case IDX_POTFILE_PATH:              user_options->potfile_path              = optarg;         break;
      case IDX_DEBUG_MODE:                user_options->debug_mode                = atoi (optarg);  break;
      case IDX_DEBUG_FILE:                user_options->debug_file                = optarg;         break;
      case IDX_INDUCTION_DIR:             user_options->induction_dir             = optarg;         break;
      case IDX_OUTFILE_CHECK_DIR:         user_options->outfile_check_dir         = optarg;         break;
      case IDX_FORCE:                     user_options->force                     = true;           break;
      case IDX_SKIP:                      user_options->skip                      = atoll (optarg); break;
      case IDX_LIMIT:                     user_options->limit                     = atoll (optarg); break;
      case IDX_KEEP_GUESSING:             user_options->keep_guessing             = true;           break;
      case IDX_KEYSPACE:                  user_options->keyspace                  = true;           break;
      case IDX_BENCHMARK:                 user_options->benchmark                 = true;           break;
      case IDX_STDOUT_FLAG:               user_options->stdout_flag               = true;           break;
      case IDX_SPEED_ONLY:                user_options->speed_only                = true;           break;
      case IDX_RESTORE_DISABLE:           user_options->restore_disable           = true;           break;
      case IDX_RESTORE_FILE_PATH:         user_options->restore_file_path         = optarg;         break;
      case IDX_STATUS:                    user_options->status                    = true;           break;
      case IDX_STATUS_TIMER:              user_options->status_timer              = atoi (optarg);  break;
      case IDX_MACHINE_READABLE:          user_options->machine_readable          = true;           break;
      case IDX_LOOPBACK:                  user_options->loopback                  = true;           break;
      case IDX_WEAK_HASH_THRESHOLD:       user_options->weak_hash_threshold       = atoi (optarg);  break;
      case IDX_SESSION:                   user_options->session                   = optarg;         break;
      case IDX_HASH_MODE:                 user_options->hash_mode                 = atoi (optarg);
                                          user_options->hash_mode_chgd            = true;           break;
      case IDX_RUNTIME:                   user_options->runtime                   = atoi (optarg);
                                          user_options->runtime_chgd              = true;           break;
      case IDX_ATTACK_MODE:               user_options->attack_mode               = atoi (optarg);
                                          user_options->attack_mode_chgd          = true;           break;
      case IDX_RP_FILE:                   user_options->rp_files[user_options->rp_files_cnt++]
                                                                                  = optarg;         break;
      case IDX_RP_GEN:                    user_options->rp_gen                    = atoi (optarg);  break;
      case IDX_RP_GEN_FUNC_MIN:           user_options->rp_gen_func_min           = atoi (optarg);  break;
      case IDX_RP_GEN_FUNC_MAX:           user_options->rp_gen_func_max           = atoi (optarg);  break;
      case IDX_RP_GEN_SEED:               user_options->rp_gen_seed               = atoi (optarg);
                                          user_options->rp_gen_seed_chgd          = true;           break;
      case IDX_RULE_BUF_L:                user_options->rule_buf_l                = optarg;         break;
      case IDX_RULE_BUF_R:                user_options->rule_buf_r                = optarg;         break;
      case IDX_MARKOV_DISABLE:            user_options->markov_disable            = true;           break;
      case IDX_MARKOV_CLASSIC:            user_options->markov_classic            = true;           break;
      case IDX_MARKOV_THRESHOLD:          user_options->markov_threshold          = atoi (optarg);  break;
      case IDX_MARKOV_HCSTAT:             user_options->markov_hcstat             = optarg;         break;
      case IDX_OUTFILE:                   user_options->outfile                   = optarg;         break;
      case IDX_OUTFILE_FORMAT:            user_options->outfile_format            = atoi (optarg);
                                          user_options->outfile_format_chgd       = true;           break;
      case IDX_OUTFILE_AUTOHEX_DISABLE:   user_options->outfile_autohex           = false;          break;
      case IDX_OUTFILE_CHECK_TIMER:       user_options->outfile_check_timer       = atoi (optarg);  break;
      case IDX_HEX_CHARSET:               user_options->hex_charset               = true;           break;
      case IDX_HEX_SALT:                  user_options->hex_salt                  = true;           break;
      case IDX_HEX_WORDLIST:              user_options->hex_wordlist              = true;           break;
      case IDX_CPU_AFFINITY:              user_options->cpu_affinity              = optarg;         break;
      case IDX_OPENCL_INFO:               user_options->opencl_info               = true;           break;
      case IDX_OPENCL_DEVICES:            user_options->opencl_devices            = optarg;         break;
      case IDX_OPENCL_PLATFORMS:          user_options->opencl_platforms          = optarg;         break;
      case IDX_OPENCL_DEVICE_TYPES:       user_options->opencl_device_types       = optarg;         break;
      case IDX_OPENCL_VECTOR_WIDTH:       user_options->opencl_vector_width       = atoi (optarg);
                                          user_options->opencl_vector_width_chgd  = true;           break;
      case IDX_WORKLOAD_PROFILE:          user_options->workload_profile          = atoi (optarg);
                                          user_options->workload_profile_chgd     = true;           break;
      case IDX_KERNEL_ACCEL:              user_options->kernel_accel              = atoi (optarg);
                                          user_options->kernel_accel_chgd         = true;           break;
      case IDX_KERNEL_LOOPS:              user_options->kernel_loops              = atoi (optarg);
                                          user_options->kernel_loops_chgd         = true;           break;
      case IDX_NVIDIA_SPIN_DAMP:          user_options->nvidia_spin_damp          = atoi (optarg);
                                          user_options->nvidia_spin_damp_chgd     = true;           break;
      case IDX_GPU_TEMP_DISABLE:          user_options->gpu_temp_disable          = true;           break;
      case IDX_GPU_TEMP_ABORT:            user_options->gpu_temp_abort            = atoi (optarg);  break;
      case IDX_GPU_TEMP_RETAIN:           user_options->gpu_temp_retain           = atoi (optarg);  break;
      case IDX_POWERTUNE_ENABLE:          user_options->powertune_enable          = true;           break;
      case IDX_LOGFILE_DISABLE:           user_options->logfile_disable           = true;           break;
      case IDX_TRUECRYPT_KEYFILES:        user_options->truecrypt_keyfiles        = optarg;         break;
      case IDX_VERACRYPT_KEYFILES:        user_options->veracrypt_keyfiles        = optarg;         break;
      case IDX_VERACRYPT_PIM:             user_options->veracrypt_pim             = atoi (optarg);  break;
      case IDX_SEGMENT_SIZE:              user_options->segment_size              = atoi (optarg);
                                          user_options->segment_size_chgd         = true;           break;
      case IDX_SCRYPT_TMTO:               user_options->scrypt_tmto               = atoi (optarg);  break;
      case IDX_SEPARATOR:                 user_options->separator                 = optarg[0];      break;
      case IDX_BITMAP_MIN:                user_options->bitmap_min                = atoi (optarg);  break;
      case IDX_BITMAP_MAX:                user_options->bitmap_max                = atoi (optarg);  break;
      case IDX_INCREMENT:                 user_options->increment                 = true;           break;
      case IDX_INCREMENT_MIN:             user_options->increment_min             = atoi (optarg);
                                          user_options->increment_min_chgd        = true;           break;
      case IDX_INCREMENT_MAX:             user_options->increment_max             = atoi (optarg);
                                          user_options->increment_max_chgd        = true;           break;
      case IDX_CUSTOM_CHARSET_1:          user_options->custom_charset_1          = optarg;         break;
      case IDX_CUSTOM_CHARSET_2:          user_options->custom_charset_2          = optarg;         break;
      case IDX_CUSTOM_CHARSET_3:          user_options->custom_charset_3          = optarg;         break;
      case IDX_CUSTOM_CHARSET_4:          user_options->custom_charset_4          = optarg;         break;

      default:
      {
        event_log_error (hashcat_ctx, "Invalid argument specified");

        return -1;
      }
    }
  }

  if (optopt != 0)
  {
    event_log_error (hashcat_ctx, "Invalid argument specified");

    return -1;
  }

  user_options->hc_bin = argv[0];

  user_options->hc_argc = argc - optind;
  user_options->hc_argv = argv + optind;

  return 0;
}

int user_options_sanity (hashcat_ctx_t *hashcat_ctx)
{
  user_options_t *user_options = hashcat_ctx->user_options;

  if (user_options->hc_argc < 0)
  {
    event_log_error (hashcat_ctx, "hc_argc %d is invalid", user_options->hc_argc);

    return -1;
  }

  if (user_options->hc_argv == NULL)
  {
    event_log_error (hashcat_ctx, "hc_argv is NULL");

    return -1;
  }

  if ((user_options->attack_mode != ATTACK_MODE_STRAIGHT)
   && (user_options->attack_mode != ATTACK_MODE_COMBI)
   && (user_options->attack_mode != ATTACK_MODE_BF)
   && (user_options->attack_mode != ATTACK_MODE_HYBRID1)
   && (user_options->attack_mode != ATTACK_MODE_HYBRID2)
   && (user_options->attack_mode != ATTACK_MODE_NONE))
  {
    event_log_error (hashcat_ctx, "Invalid attack-mode specified");

    return -1;
  }

  if (user_options->runtime_chgd == true && user_options->runtime == 0)
  {
    event_log_error (hashcat_ctx, "Invalid runtime specified");

    return -1;
  }

  if (user_options->hash_mode > 99999)
  {
    event_log_error (hashcat_ctx, "Invalid hash-type specified");

    return -1;
  }

  if (user_options->username == true)
  {
    if  ((user_options->hash_mode ==  2500)
     ||  (user_options->hash_mode ==  5200)
     || ((user_options->hash_mode >=  6200) && (user_options->hash_mode <=  6299))
     || ((user_options->hash_mode >= 13700) && (user_options->hash_mode <= 13799))
     ||  (user_options->hash_mode ==  9000))
    {
      event_log_error (hashcat_ctx, "Mixing support for user names and hashes of type %s is not supported", strhashtype (user_options->hash_mode));

      return -1;
    }
  }

  if (user_options->outfile_format > 16)
  {
    event_log_error (hashcat_ctx, "Invalid outfile-format specified");

    return -1;
  }

  if (user_options->left == true)
  {
    if (user_options->outfile_format_chgd == true)
    {
      if (user_options->outfile_format > 1)
      {
        event_log_error (hashcat_ctx, "Mixing outfile-format > 1 with left parameter is not allowed");

        return -1;
      }
    }
  }

  if (user_options->show == true)
  {
    if (user_options->outfile_format_chgd == true)
    {
      if (user_options->outfile_format > 7)
      {
        event_log_error (hashcat_ctx, "Mixing outfile-format > 7 with show parameter is not allowed");

        return -1;
      }
    }
  }

  if (user_options->increment_min < INCREMENT_MIN)
  {
    event_log_error (hashcat_ctx, "Invalid increment-min specified");

    return -1;
  }

  if (user_options->increment_max > INCREMENT_MAX)
  {
    event_log_error (hashcat_ctx, "Invalid increment-max specified");

    return -1;
  }

  if (user_options->increment_min > user_options->increment_max)
  {
    event_log_error (hashcat_ctx, "Invalid increment-min specified");

    return -1;
  }

  if ((user_options->increment == true) && (user_options->attack_mode == ATTACK_MODE_STRAIGHT))
  {
    event_log_error (hashcat_ctx, "Increment is not allowed in attack-mode 0");

    return -1;
  }

  if ((user_options->increment == false) && (user_options->increment_min_chgd == true))
  {
    event_log_error (hashcat_ctx, "Increment-min is only supported combined with increment switch");

    return -1;
  }

  if ((user_options->increment == false) && (user_options->increment_max_chgd == true))
  {
    event_log_error (hashcat_ctx, "Increment-max is only supported combined with increment switch");

    return -1;
  }

  if (user_options->rp_files_cnt > 0 && user_options->rp_gen == true)
  {
    event_log_error (hashcat_ctx, "Use of both rules-file and rules-generate is not supported");

    return -1;
  }

  if (user_options->rp_files_cnt > 0 || user_options->rp_gen == true)
  {
    if (user_options->attack_mode != ATTACK_MODE_STRAIGHT)
    {
      event_log_error (hashcat_ctx, "Use of rules-file or rules-generate only allowed in attack-mode 0");

      return -1;
    }
  }

  if (user_options->bitmap_min > user_options->bitmap_max)
  {
    event_log_error (hashcat_ctx, "Invalid bitmap-min specified");

    return -1;
  }

  if (user_options->rp_gen_func_min > user_options->rp_gen_func_max)
  {
    event_log_error (hashcat_ctx, "Invalid rp-gen-func-min specified");

    return -1;
  }

  if (user_options->kernel_accel_chgd == true)
  {
    if (user_options->force == false)
    {
      event_log_error (hashcat_ctx, "The manual use of the -n option (or --kernel-accel) is outdated.");
      event_log_error (hashcat_ctx, "Please consider using the -w option instead.");
      event_log_error (hashcat_ctx, "You can use --force to override this but do not post error reports if you do so.");

      return -1;
    }

    if (user_options->kernel_accel < 1)
    {
      event_log_error (hashcat_ctx, "Invalid kernel-accel specified");

      return -1;
    }

    if (user_options->kernel_accel > 1024)
    {
      event_log_error (hashcat_ctx, "Invalid kernel-accel specified");

      return -1;
    }
  }

  if (user_options->kernel_loops_chgd == true)
  {
    if (user_options->force == false)
    {
      event_log_error (hashcat_ctx, "The manual use of the -u option (or --kernel-loops) is outdated.");
      event_log_error (hashcat_ctx, "Please consider using the -w option instead.");
      event_log_error (hashcat_ctx, "You can use --force to override this but do not post error reports if you do so.");

      return -1;
    }

    if (user_options->kernel_loops < 1)
    {
      event_log_error (hashcat_ctx, "Invalid kernel-loops specified");

      return -1;
    }

    if (user_options->kernel_loops > 1024)
    {
      event_log_error (hashcat_ctx, "Invalid kernel-loops specified");

      return -1;
    }
  }

  if ((user_options->workload_profile < 1) || (user_options->workload_profile > 4))
  {
    event_log_error (hashcat_ctx, "workload-profile %i not available", user_options->workload_profile);

    return -1;
  }

  if (user_options->opencl_vector_width_chgd == true)
  {
    if (is_power_of_2 (user_options->opencl_vector_width) == false || user_options->opencl_vector_width > 16)
    {
      event_log_error (hashcat_ctx, "opencl-vector-width %i not allowed", user_options->opencl_vector_width);

      return -1;
    }
  }

  if (user_options->show == true || user_options->left == true)
  {
    if (user_options->remove == true)
    {
      event_log_error (hashcat_ctx, "Mixing remove parameter not allowed with show parameter or left parameter");

      return -1;
    }

    if (user_options->potfile_disable == true)
    {
      event_log_error (hashcat_ctx, "Mixing potfile-disable parameter not allowed with show parameter or left parameter");

      return -1;
    }
  }

  if (user_options->show == true)
  {
    if (user_options->outfile_autohex == false)
    {
      event_log_error (hashcat_ctx, "Mixing outfile-autohex-disable parameter not allowed with show parameter");

      return -1;
    }
  }

  if (user_options->keyspace == true)
  {
    if (user_options->show == true)
    {
      event_log_error (hashcat_ctx, "Combining show parameter with keyspace parameter is not allowed");

      return -1;
    }
    else if (user_options->left == true)
    {
      event_log_error (hashcat_ctx, "Combining left parameter with keyspace parameter is not allowed");

      return -1;
    }
  }

  if (user_options->remove_timer_chgd == true)
  {
    if (user_options->remove == false)
    {
      event_log_error (hashcat_ctx, "Parameter remove-timer require parameter remove enabled");

      return -1;
    }

    if (user_options->remove_timer < 1)
    {
      event_log_error (hashcat_ctx, "Parameter remove-timer must have a value greater than or equal to 1");

      return -1;
    }
  }

  if (user_options->loopback == true)
  {
    if (user_options->attack_mode == ATTACK_MODE_STRAIGHT)
    {
      if ((user_options->rp_files_cnt == 0) && (user_options->rp_gen == 0))
      {
        event_log_error (hashcat_ctx, "Parameter loopback not allowed without rules-file or rules-generate");

        return -1;
      }
    }
    else
    {
      event_log_error (hashcat_ctx, "Parameter loopback allowed in attack-mode 0 only");

      return -1;
    }
  }


  if (user_options->debug_mode > 0)
  {
    if (user_options->attack_mode != ATTACK_MODE_STRAIGHT)
    {
      event_log_error (hashcat_ctx, "Parameter debug-mode option is only available with attack-mode 0");

      return -1;
    }

    if ((user_options->rp_files_cnt == 0) && (user_options->rp_gen == 0))
    {
      event_log_error (hashcat_ctx, "Parameter debug-mode not allowed without rules-file or rules-generate");

      return -1;
    }
  }

  if (user_options->debug_mode > 4)
  {
    event_log_error (hashcat_ctx, "Invalid debug-mode specified");

    return -1;
  }

  if (user_options->debug_file != NULL)
  {
    if (user_options->debug_mode < 1)
    {
      event_log_error (hashcat_ctx, "Parameter debug-file requires parameter debug-mode to be set");

      return -1;
    }
  }

  if (user_options->induction_dir != NULL)
  {
    if (user_options->attack_mode == ATTACK_MODE_BF)
    {
      event_log_error (hashcat_ctx, "Parameter induction-dir not allowed with brute-force attacks");

      return -1;
    }
  }

  if (user_options->attack_mode != ATTACK_MODE_STRAIGHT)
  {
    if ((user_options->weak_hash_threshold != WEAK_HASH_THRESHOLD) && (user_options->weak_hash_threshold != 0))
    {
      event_log_error (hashcat_ctx, "setting --weak-hash-threshold allowed only in straight-attack mode");

      return -1;
    }
  }

  if (user_options->nvidia_spin_damp > 100)
  {
    event_log_error (hashcat_ctx, "setting --nvidia-spin-damp must be between 0 and 100 (inclusive)");

    return -1;
  }

  if ((user_options->gpu_temp_abort != 0) && (user_options->gpu_temp_retain != 0))
  {
    if (user_options->gpu_temp_abort < user_options->gpu_temp_retain)
    {
      event_log_error (hashcat_ctx, "Invalid values for gpu-temp-abort. Parameter gpu-temp-abort is less than gpu-temp-retain.");

      return -1;
    }
  }

  if (user_options->benchmark == true)
  {
    if (user_options->attack_mode_chgd == true)
    {
      if (user_options->attack_mode != ATTACK_MODE_BF)
      {
        event_log_error (hashcat_ctx, "Only attack-mode 3 allowed in benchmark mode");

        return -1;
      }
    }
  }

  // argc / argv checks

  bool show_error = true;

  if (user_options->version == true)
  {
    show_error = false;
  }
  else if (user_options->usage == true)
  {
    show_error = false;
  }
  else if (user_options->benchmark == true)
  {
    if (user_options->hc_argc == 0)
    {
      show_error = false;
    }
  }
  else if (user_options->opencl_info == true)
  {
    if (user_options->hc_argc == 0)
    {
      show_error = false;
    }
  }
  else if (user_options->restore == true)
  {
    if (user_options->hc_argc == 0)
    {
      show_error = false;
    }
  }
  else if (user_options->keyspace == true)
  {
    if (user_options->attack_mode == ATTACK_MODE_STRAIGHT)
    {
      if (user_options->hc_argc == 1)
      {
        show_error = false;
      }
    }
    else if (user_options->attack_mode == ATTACK_MODE_COMBI)
    {
      if (user_options->hc_argc == 2)
      {
        show_error = false;
      }
    }
    else if (user_options->attack_mode == ATTACK_MODE_BF)
    {
      if (user_options->hc_argc == 1)
      {
        show_error = false;
      }
    }
    else if (user_options->attack_mode == ATTACK_MODE_HYBRID1)
    {
      if (user_options->hc_argc == 2)
      {
        show_error = false;
      }
    }
    else if (user_options->attack_mode == ATTACK_MODE_HYBRID2)
    {
      if (user_options->hc_argc == 2)
      {
        show_error = false;
      }
    }
  }
  else if (user_options->stdout_flag == true)
  {
    if (user_options->attack_mode == ATTACK_MODE_STRAIGHT)
    {
      // all argc possible because of stdin mode

      show_error = false;
    }
    else if (user_options->attack_mode == ATTACK_MODE_COMBI)
    {
      if (user_options->hc_argc == 2)
      {
        show_error = false;
      }
    }
    else if (user_options->attack_mode == ATTACK_MODE_BF)
    {
      if (user_options->hc_argc >= 1)
      {
        show_error = false;
      }
    }
    else if (user_options->attack_mode == ATTACK_MODE_HYBRID1)
    {
      if (user_options->hc_argc >= 1)
      {
        show_error = false;
      }
    }
    else if (user_options->attack_mode == ATTACK_MODE_HYBRID2)
    {
      if (user_options->hc_argc >= 1)
      {
        show_error = false;
      }
    }
  }
  else
  {
    if (user_options->attack_mode == ATTACK_MODE_STRAIGHT)
    {
      if (user_options->hc_argc >= 1)
      {
        show_error = false;
      }
    }
    else if (user_options->attack_mode == ATTACK_MODE_COMBI)
    {
      if (user_options->hc_argc == 3)
      {
        show_error = false;
      }
    }
    else if (user_options->attack_mode == ATTACK_MODE_BF)
    {
      if (user_options->hc_argc >= 1)
      {
        show_error = false;
      }
    }
    else if (user_options->attack_mode == ATTACK_MODE_HYBRID1)
    {
      if (user_options->hc_argc >= 2)
      {
        show_error = false;
      }
    }
    else if (user_options->attack_mode == ATTACK_MODE_HYBRID2)
    {
      if (user_options->hc_argc >= 2)
      {
        show_error = false;
      }
    }
  }

  if (show_error == true)
  {
    usage_mini_print (user_options->hc_bin);

    return -1;
  }

  return 0;
}

void user_options_preprocess (hashcat_ctx_t *hashcat_ctx)
{
  user_options_t *user_options = hashcat_ctx->user_options;

  #if !defined (WITH_HWMON)
  user_options->powertune_enable = false;
  user_options->gpu_temp_disable = true;
  user_options->gpu_temp_abort   = 0;
  user_options->gpu_temp_retain  = 0;
  #endif // WITH_HWMON

  // some options can influence or overwrite other options

  if (user_options->opencl_info == true
   || user_options->keyspace    == true
   || user_options->benchmark   == true
   || user_options->stdout_flag == true
   || user_options->speed_only  == true)
  {
    user_options->show                = false;
    user_options->left                = false;
    user_options->gpu_temp_disable    = true;
    user_options->potfile_disable     = true;
    user_options->powertune_enable    = false;
    user_options->restore             = false;
    user_options->restore_disable     = true;
    user_options->restore_timer       = 0;
    user_options->logfile_disable     = true;
    user_options->weak_hash_threshold = 0;
    user_options->nvidia_spin_damp    = 0;
    user_options->status              = false;
    user_options->status_timer        = 0;
    user_options->outfile_check_timer = 0;
  }

  if (user_options->benchmark == true)
  {
    user_options->session             = "benchmark";
    user_options->attack_mode         = ATTACK_MODE_BF;
    user_options->increment           = false;
    user_options->speed_only          = true;

    if (user_options->workload_profile_chgd == false)
    {
      user_options->workload_profile = 3;
    }

    if (user_options->powertune_enable == true)
    {
      user_options->gpu_temp_disable = false;
    }
  }

  if (user_options->keyspace == true)
  {
    user_options->session             = "keyspace";
    user_options->quiet               = true;
  }

  if (user_options->stdout_flag == true)
  {
    user_options->session             = "stdout";
    user_options->quiet               = true;
    user_options->hash_mode           = 2000;
    user_options->outfile_format      = OUTFILE_FMT_PLAIN;
    user_options->force               = true;
    user_options->kernel_accel        = 1024;
    user_options->kernel_loops        = 1024;
    user_options->opencl_vector_width = 1;
  }

  if (user_options->opencl_info == true)
  {
    user_options->session             = "opencl_info";
    user_options->quiet               = true;
    user_options->opencl_platforms    = NULL;
    user_options->opencl_devices      = NULL;
    user_options->opencl_device_types = hcstrdup (hashcat_ctx, "1,2,3");
  }

  if (user_options->left == true)
  {
    user_options->outfile_format = OUTFILE_FMT_HASH;
  }

  if (user_options->show == true || user_options->left == true)
  {
    user_options->attack_mode = ATTACK_MODE_NONE;
    user_options->quiet       = true;
  }

  // this allows the user to use --show and --left while cracking (i.e. while another instance of hashcat is running)
  if (user_options->show == true || user_options->left == true)
  {
    user_options->restore_disable = true;

    user_options->restore = false;
  }

  if (user_options->skip != 0 && user_options->limit != 0)
  {
    user_options->limit += user_options->skip;
  }

  if (user_options->attack_mode != ATTACK_MODE_STRAIGHT)
  {
    user_options->weak_hash_threshold = 0;
  }

  if (user_options->hash_mode == 9710)
  {
    user_options->outfile_format      = 5;
    user_options->outfile_format_chgd = 1;
  }

  if (user_options->hash_mode == 9810)
  {
    user_options->outfile_format      = 5;
    user_options->outfile_format_chgd = 1;
  }

  if (user_options->hash_mode == 10410)
  {
    user_options->outfile_format      = 5;
    user_options->outfile_format_chgd = 1;
  }

  if (user_options->markov_threshold == 0)
  {
    user_options->markov_threshold = 0x100;
  }

  if (user_options->segment_size_chgd == true)
  {
    user_options->segment_size *= (1024 * 1024);
  }

  if (user_options->gpu_temp_disable == true)
  {
    user_options->gpu_temp_abort  = 0;
    user_options->gpu_temp_retain = 0;
  }

  // default mask

  if (user_options->attack_mode == ATTACK_MODE_BF)
  {
    if (user_options->benchmark == true)
    {

    }
    else if (user_options->opencl_info == true)
    {

    }
    else if (user_options->keyspace == true)
    {
      if (user_options->hc_argc == 0)
      {
        user_options->custom_charset_1 = DEF_MASK_CS_1;
        user_options->custom_charset_2 = DEF_MASK_CS_2;
        user_options->custom_charset_3 = DEF_MASK_CS_3;

        user_options->increment = true;
      }
    }
    else if (user_options->stdout_flag == true)
    {
      if (user_options->hc_argc == 0)
      {
        user_options->custom_charset_1 = DEF_MASK_CS_1;
        user_options->custom_charset_2 = DEF_MASK_CS_2;
        user_options->custom_charset_3 = DEF_MASK_CS_3;

        user_options->increment = true;
      }
    }
    else
    {
      if (user_options->hc_argc == 1)
      {
        user_options->custom_charset_1 = DEF_MASK_CS_1;
        user_options->custom_charset_2 = DEF_MASK_CS_2;
        user_options->custom_charset_3 = DEF_MASK_CS_3;

        user_options->increment = true;
      }
    }
  }
}

void user_options_extra_init (hashcat_ctx_t *hashcat_ctx)
{
  user_options_t       *user_options       = hashcat_ctx->user_options;
  user_options_extra_t *user_options_extra = hashcat_ctx->user_options_extra;

  // attack-kern

  user_options_extra->attack_kern = ATTACK_KERN_NONE;

  switch (user_options->attack_mode)
  {
    case ATTACK_MODE_STRAIGHT: user_options_extra->attack_kern = ATTACK_KERN_STRAIGHT; break;
    case ATTACK_MODE_COMBI:    user_options_extra->attack_kern = ATTACK_KERN_COMBI;    break;
    case ATTACK_MODE_BF:       user_options_extra->attack_kern = ATTACK_KERN_BF;       break;
    case ATTACK_MODE_HYBRID1:  user_options_extra->attack_kern = ATTACK_KERN_COMBI;    break;
    case ATTACK_MODE_HYBRID2:  user_options_extra->attack_kern = ATTACK_KERN_COMBI;    break;
  }

  // rules

  user_options_extra->rule_len_l = (int) strlen (user_options->rule_buf_l);
  user_options_extra->rule_len_r = (int) strlen (user_options->rule_buf_r);

  // hc_hash and hc_work*

  user_options_extra->hc_hash  = NULL;
  user_options_extra->hc_workv = NULL;
  user_options_extra->hc_workc = 0;

  if (user_options->benchmark == true)
  {

  }
  else if (user_options->opencl_info == true)
  {

  }
  else if (user_options->keyspace == true)
  {
    user_options_extra->hc_workc = user_options->hc_argc;
    user_options_extra->hc_workv = user_options->hc_argv;
  }
  else if (user_options->stdout_flag == true)
  {
    user_options_extra->hc_workc = user_options->hc_argc;
    user_options_extra->hc_workv = user_options->hc_argv;
  }
  else
  {
    user_options_extra->hc_hash  = user_options->hc_argv[0];
    user_options_extra->hc_workc = user_options->hc_argc - 1;
    user_options_extra->hc_workv = user_options->hc_argv + 1;
  }

  // wordlist_mode

  user_options_extra->wordlist_mode = WL_MODE_NONE;

  if (user_options_extra->attack_kern == ATTACK_KERN_STRAIGHT)
  {
    user_options_extra->wordlist_mode = (user_options_extra->hc_workc >= 1) ? WL_MODE_FILE : WL_MODE_STDIN;
  }
  else if (user_options_extra->attack_kern == ATTACK_KERN_COMBI)
  {
    user_options_extra->wordlist_mode = WL_MODE_FILE;
  }
  else if (user_options_extra->attack_kern == ATTACK_KERN_BF)
  {
    user_options_extra->wordlist_mode = WL_MODE_MASK;
  }
}

void user_options_extra_destroy (hashcat_ctx_t *hashcat_ctx)
{
  user_options_extra_t *user_options_extra = hashcat_ctx->user_options_extra;

  memset (user_options_extra, 0, sizeof (user_options_extra_t));
}

u64 user_options_extra_amplifier (hashcat_ctx_t *hashcat_ctx)
{
  const combinator_ctx_t     *combinator_ctx     = hashcat_ctx->combinator_ctx;
  const mask_ctx_t           *mask_ctx           = hashcat_ctx->mask_ctx;
  const straight_ctx_t       *straight_ctx       = hashcat_ctx->straight_ctx;
  const user_options_extra_t *user_options_extra = hashcat_ctx->user_options_extra;

  if (user_options_extra->attack_kern == ATTACK_KERN_STRAIGHT)
  {
    if (straight_ctx->kernel_rules_cnt)
    {
      return straight_ctx->kernel_rules_cnt;
    }
  }
  else if (user_options_extra->attack_kern == ATTACK_KERN_COMBI)
  {
    if (combinator_ctx->combs_cnt)
    {
      return combinator_ctx->combs_cnt;
    }
  }
  else if (user_options_extra->attack_kern == ATTACK_KERN_BF)
  {
    if (mask_ctx->bfs_cnt)
    {
      return mask_ctx->bfs_cnt;
    }
  }

  return 1;
}

void user_options_logger (hashcat_ctx_t *hashcat_ctx)
{
  user_options_t *user_options = hashcat_ctx->user_options;
  logfile_ctx_t  *logfile_ctx  = hashcat_ctx->logfile_ctx;

  logfile_top_char   (user_options->separator);
  logfile_top_string (user_options->cpu_affinity);
  logfile_top_string (user_options->custom_charset_1);
  logfile_top_string (user_options->custom_charset_2);
  logfile_top_string (user_options->custom_charset_3);
  logfile_top_string (user_options->custom_charset_4);
  logfile_top_string (user_options->debug_file);
  logfile_top_string (user_options->induction_dir);
  logfile_top_string (user_options->markov_hcstat);
  logfile_top_string (user_options->opencl_devices);
  logfile_top_string (user_options->opencl_device_types);
  logfile_top_string (user_options->opencl_platforms);
  logfile_top_string (user_options->outfile);
  logfile_top_string (user_options->outfile_check_dir);
  logfile_top_string (user_options->potfile_path);
  logfile_top_string (user_options->restore_file_path);
  logfile_top_string (user_options->rp_files[0]);
  logfile_top_string (user_options->rule_buf_l);
  logfile_top_string (user_options->rule_buf_r);
  logfile_top_string (user_options->session);
  logfile_top_string (user_options->truecrypt_keyfiles);
  logfile_top_string (user_options->veracrypt_keyfiles);
  logfile_top_uint64 (user_options->limit);
  logfile_top_uint64 (user_options->skip);
  logfile_top_uint   (user_options->attack_mode);
  logfile_top_uint   (user_options->benchmark);
  logfile_top_uint   (user_options->bitmap_max);
  logfile_top_uint   (user_options->bitmap_min);
  logfile_top_uint   (user_options->debug_mode);
  logfile_top_uint   (user_options->force);
  logfile_top_uint   (user_options->gpu_temp_abort);
  logfile_top_uint   (user_options->gpu_temp_disable);
  logfile_top_uint   (user_options->gpu_temp_retain);
  logfile_top_uint   (user_options->hash_mode);
  logfile_top_uint   (user_options->hex_charset);
  logfile_top_uint   (user_options->hex_salt);
  logfile_top_uint   (user_options->hex_wordlist);
  logfile_top_uint   (user_options->increment);
  logfile_top_uint   (user_options->increment_max);
  logfile_top_uint   (user_options->increment_min);
  logfile_top_uint   (user_options->keep_guessing);
  logfile_top_uint   (user_options->kernel_accel);
  logfile_top_uint   (user_options->kernel_loops);
  logfile_top_uint   (user_options->keyspace);
  logfile_top_uint   (user_options->left);
  logfile_top_uint   (user_options->logfile_disable);
  logfile_top_uint   (user_options->loopback);
  logfile_top_uint   (user_options->machine_readable);
  logfile_top_uint   (user_options->markov_classic);
  logfile_top_uint   (user_options->markov_disable);
  logfile_top_uint   (user_options->markov_threshold);
  logfile_top_uint   (user_options->nvidia_spin_damp);
  logfile_top_uint   (user_options->opencl_info);
  logfile_top_uint   (user_options->opencl_vector_width);
  logfile_top_uint   (user_options->outfile_autohex);
  logfile_top_uint   (user_options->outfile_check_timer);
  logfile_top_uint   (user_options->outfile_format);
  logfile_top_uint   (user_options->potfile_disable);
  logfile_top_uint   (user_options->powertune_enable);
  logfile_top_uint   (user_options->quiet);
  logfile_top_uint   (user_options->remove);
  logfile_top_uint   (user_options->remove_timer);
  logfile_top_uint   (user_options->restore);
  logfile_top_uint   (user_options->restore_disable);
  logfile_top_uint   (user_options->restore_timer);
  logfile_top_uint   (user_options->rp_files_cnt);
  logfile_top_uint   (user_options->rp_gen);
  logfile_top_uint   (user_options->rp_gen_func_max);
  logfile_top_uint   (user_options->rp_gen_func_min);
  logfile_top_uint   (user_options->rp_gen_seed);
  logfile_top_uint   (user_options->runtime);
  logfile_top_uint   (user_options->scrypt_tmto);
  logfile_top_uint   (user_options->segment_size);
  logfile_top_uint   (user_options->show);
  logfile_top_uint   (user_options->status);
  logfile_top_uint   (user_options->status_timer);
  logfile_top_uint   (user_options->stdout_flag);
  logfile_top_uint   (user_options->speed_only);
  logfile_top_uint   (user_options->usage);
  logfile_top_uint   (user_options->username);
  logfile_top_uint   (user_options->veracrypt_pim);
  logfile_top_uint   (user_options->version);
  logfile_top_uint   (user_options->weak_hash_threshold);
  logfile_top_uint   (user_options->workload_profile);
}
