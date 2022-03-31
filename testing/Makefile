cc=clang
cc_flags=-std=c99 -Wall
cc_defs=-DFARL_LOG_PATHS -DFARL_LOG_RESOLVING -DFARL_LOG_BUILDING -DFARL_LOG_STDOUT
cc_defs=-DFARL_LOG_RESOLVING -DFARL_LOG_STDOUT
cc_dep_btree=../btree/btree.h ../btree/btree.c
cc_src_btree=../btree/btree.c
cc_dep_log=../farl/log.h ../farl/..log.c
cc_src_log=../farl/log.c
cc_dep_hooks=../farl/hooks.h ../farl/hooks.c
cc_src_hooks=../farl/hooks.c
cc_dep_mappings=../farl/mappings.h ../farl/mappings.c
cc_src_mappings=../farl/mappings.c
cc_dep_test=test.c
cc_src_test=test.c

all: clean test

test: test.o btree.o log.o mappings.o
	$(cc) $(cc_flags) $(cc_defs) -lm test.o btree.o log.o mappings.o -o test

test.o: $(cc_dep_test)
	$(cc) $(cc_flags) $(cc_defs) -O -c $(cc_src_test)

mappings.o: $(cc_dep_mappings)
	$(cc) $(cc_flags) $(cc_defs) -O -c $(cc_src_mappings)

log.o: $(cc_dep_farl)
	$(cc) $(cc_flags) $(cc_defs) -O -c $(cc_src_log)

btree.o: $(cc_dep_btree)
	$(cc) $(cc_flags) $(cc_defs) -O -c $(cc_src_btree)

clean:
	rm -f *.o
	rm -f *.so
	rm -f test
