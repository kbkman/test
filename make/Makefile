
OUTPUT = hello world
$(warning OUTPUT=$(OUTPUT))

ifndef OUTPUT
  $(error undefined OUTPUT)
else
  OUTPUT += end
  $(warning OUTPUT=$(OUTPUT))
endif

define test
	@echo $1
endef

all:
	echo $(SHELL)
	echo $(OUTPUT)
	$(call test,this is test first param)
	$(warning this is warning)


.PHONY: one all

