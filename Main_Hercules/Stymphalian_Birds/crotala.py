from __future__ import print_function
import os
import sys
import errno

def check_args():
	for s in sys.argv:
		if s == "-libft":
			get_libft(path)
		if s == '-web':
			create_path_web(path)
			return
	create_path_c(path)


def print_help():
	print("Flags:");
	prinnt("\t-libft\tInclude libft in project folder")
	print("\t-web\tMake web directory template")

def get_libft(path):
	os.system('git submodule add vogsphere@vgs.42.us.org:intra/2016/activities/libft/thendric2 ' + path + '/libft')

def create_path_c(path):
	try:
		os.makedirs(path)
		os.makedirs(path + "/srcs")
		os.makedirs(path + "/inc")
		f1 = open(path + "/.gitignore", "a+")
		f2 = open(path + "/author", "a+")
		f2.write("thendric\n")
		f1.close
		f2.close
		os.system('cp Makefile ' + path)
	except OSError as exception:
		if exception.errno != errno.EEXIST:
			raise

def create_path_web(path):
	try:
		os.makedirs(path)
		os.makedirs(path + "/css")
		os.makedirs(path + "/img")
		os.makedirs(path + "/js")
		f1 = open(path + "/.gitignore", "a+")
		f2 = open(path + "/index.html", "a+")
		f2.write("<!DOCTYPE html>\n<html>\n\t<head>\n\t</head>\n\t<body>\n\t</body>\n</html>")
		f1.close
		f2.close
	except OSError as exception:
		if exception.errno != errno.EEXIST:
			raise

for s in sys.argv:
	if s == "-help":
		print_help()
		exit()

print("Project name: ",end='')
path = raw_input()

check_args()
