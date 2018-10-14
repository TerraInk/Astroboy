# this makefile is not for download, it is just a utility on the
# server to create the gz archive from the source directory

VER=2.07.01
FILE=swe_unix_src_$(VER).tar
s:	
	tar cvf $(FILE) src doc/*gif doc/*pdf doc/*htm
	gzip -f $(FILE)
	chmod 664 $(FILE).gz
	echo "Content of sweph.zip\n" > swephzip.txt
	unzip -v sweph.zip >> swephzip.txt
	cp -p doc/*htm /wwd/swisseph
	cp -p doc/*pdf /wwd/swisseph
