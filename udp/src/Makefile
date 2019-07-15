$(if $(findstring d,abc),$(warning aaaa))
test : $(shell ls *.cpp 2>/dev/null)
	if [ -n "$^" ]; then \
		$(CXX) -o $@ $^; \
	fi


clean :
	rm -rf *.o test

