
OUTPUT = hello world
#$(warning OUTPUT=$(OUTPUT))

ifndef OUTPUT
  $(warning undefined OUTPUT)
else
  #OUTPUT += end
  $(warning OUTPUT=$(OUTPUT))
endif

$(warning $(if $(findstring hello,$(OUTPUT)),yes,no))

define test
	@echo $1
endef

define getpid
	@pidof $1 2>/dev/null || echo 0
	-@pidof ssh
endef

all:
	echo $(SHELL)
	echo $(OUTPUT)
	$(call test,this is test first param)
	$(warning this is warning)
	$(call getpid,ddd)


.PHONY: one all

