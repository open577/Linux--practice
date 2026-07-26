# Makefile
libmystdio.so:my_stdio.o my_string.o
	gcc -o $@ $^ -shared
%.o:%.c
	gcc -fPIC -c $<

.PHONY:clean
clean:
	@rm -rf *.so *.o stdc*
	@echo "clean ... done"

.PHONY:output
output:
	@mkdir -p stdc/include
	@mkdir -p stdc/lib
	@cp -f *.h stdc/include
	@cp -f *.so stdc/lib
	@tar -czf stdc.tgz stdc
	@echo "output stdc ... done"
