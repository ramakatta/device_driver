gcc -g -o evenodd evenodd.c
#perf probe  -x evenodd -a even
Added new event:
  probe_evenodd:even   (on even in /home/rama/Downloads/Corporate_trainings/HP_training/user_space/5-Debug/gdb_pc/evenodd)

You can now use it in all perf tools, such as:
 perf record -e probe_evenodd:even -ag

perf report perf.data
