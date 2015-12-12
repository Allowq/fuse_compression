all:
	mkdir -p mountdir
	mkdir -p rootdir
	echo "zlib 1" > rootdir/.cmprs_set

distdir:
	cp Makefile $(distdir)

mostlyclean clean distclean mainainer-clean:
	rm -r mountdir rootdir
