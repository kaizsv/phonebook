CC ?= gcc
      CFLAGS_common ?= -O0 -Wall -std=gnu99

                                      EXEC = phonebook_orig phonebook_opt
                                              all: $(EXEC)
                                              perf = ./phonebook_opt

                                                      SRCS_common = main.c

                                                              phonebook_orig: $(SRCS_common) phonebook_orig.c phonebook_orig.h
                                                              $(CC) $(CFLAGS_common) -DIMPL="\"$@.h\"" -o $@ \
                                                                      $(SRCS_common) $@.c

                                                                      phonebook_opt: $(SRCS_common) phonebook_opt.c phonebook_opt.h
                                                                      $(CC) $(CFLAGS_common) -DIMPL="\"$@.h\"" -o $@ \
                                                                              $(SRCS_common) $@.c

                                                                              run: $(EXEC)
                                                                              watch -d -t ./phonebook_opt

                                                                              clean:
                                                                              $(RM) $(EXEC) *.o perf.*

                                                                              pstat: $(perf)
                                                                              perf stat -r 100 -e cache-misses,cache-references,cycles,instructions,branch-misses $(perf)

                                                                              precord: $(perf)
                                                                              perf record -e cache-misses:u $(perf) && perf report

                                                                              cache:
                                                                              echo "echo 1 > /proc/sys/vm/drop_caches" | sudo sh && ./phonebook_opt