.PHONY: clean re test

FT_NM = ../../ft_nm
NM = /usr/bin/nm

FT_OTOOL = ../../ft_otool
OTOOL = /usr/bin/otool

# DISPLAY = DEFINED

#__________FUNCTIONS__________#
define diff_file_nm
	@echo ________________NM__________________
	@$(FT_NM) $(1) > diff_ft_nm
	@$(NM) $(1) > diff_nm
	@echo $(1)
	$(if $(DISPLAY), cat diff_ft_nm diff_nm)
	diff diff_nm diff_ft_nm
	@echo ____________________________________
endef

define diff_file_otool
	@echo ______________OTOOL__________________
	@$(FT_OTOOL) $(1) > diff_ft_otool
	@$(OTOOL) -t $(1) > diff_otool
	@echo $(1)
	$(if $(DISPLAY), cat diff_ft_otool diff_otool)
	diff diff_otool diff_ft_otool
	@echo ____________________________________
endef
# cat diff_ft_otool
# cat diff_otool

#____________RULES____________#
all:
	cc -arch i386 -c test.c
	cc -arch i386 -c test_facile.c
	cc -arch i386 -c test_moins_facile.c

	cc test_facile.c -o test_facile
	cc test_moins_facile.c -o test_moins_facile
	cc -m32 test_moins_facile.c -o test_moins_facile_32-bit
	cc -arch i386 -arch x86_64 test_moins_facile.c -o test_moins_facile_universal
	cc test.c -o test_non_external -fvisibility=hidden
	cc test.c -o test_debug -g

clean:
	rm -f test.o
	rm -f test_facile.o
	rm -f test_moins_facile.o

	rm -f test_facile
	rm -f test_moins_facile
	rm -f test_moins_facile_32-bit
	rm -f test_moins_facile_universal
	rm -f test_non_external
	rm -f test_debug

re: clean all

test-nm:
	$(call diff_file_nm, test_facile)
	$(call diff_file_nm, test_moins_facile)
	$(call diff_file_nm, test_moins_facile_32-bit)
	$(call diff_file_nm, test_moins_facile_universal)
	$(call diff_file_nm, test_non_external)
	$(call diff_file_nm, test_debug)
# Arguments multiple
	$(call diff_file_nm, test_facile test_facile)
	$(call diff_file_nm, test_moins_facile_universal test_moins_facile_universal)
# Dynamic library
	$(call diff_file_nm, /usr/lib/libgmalloc.dylib)
	$(call diff_file_nm, /usr/lib/libtidy.dylib)
# Object file
	$(call diff_file_nm, test.o test_facile.o test_moins_facile.o)
# Binary
	$(call diff_file_nm, /usr/bin/python)
# Archive
	$(call diff_file_nm, /usr/lib/liby.a)

test-otool:
	$(call diff_file_otool, test_facile)
	$(call diff_file_otool, test_moins_facile)
	$(call diff_file_otool, test_moins_facile_32-bit)
	$(call diff_file_otool, test_moins_facile_universal)
	$(call diff_file_otool, test_non_external)
	$(call diff_file_otool, test_debug)
# Arguments multiple
	$(call diff_file_otool, test_facile test_facile)
	$(call diff_file_otool, test_moins_facile_universal test_moins_facile_universal)
# Dynamic library
	$(call diff_file_otool, /usr/lib/libgmalloc.dylib)
	$(call diff_file_otool, /usr/lib/libtidy.dylib)
# Object file
	$(call diff_file_otool, test.o test_facile.o test_moins_facile.o)
# Binary
	$(call diff_file_otool, /usr/bin/python)
# Archive
# $(call diff_file_otool, /usr/lib/liby.a)


test: test-nm test-otool
