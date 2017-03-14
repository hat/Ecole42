# -*- coding: utf-8 -*-
import requests
import sys
import urllib2
import contextlib
import json
import os
from tabulate import tabulate

uid = "1f117c968b63eab7dca2cc7d40b8291ec2f957dafea9a3bf68c4e021ffab92be"
secret = "01811c0418688145ed48d5cac69c4046efe7cd9f0dc61de713e53c3b60cc64ed"

'''
Finds the locations of all active users
'''

r = requests.post("https://api.intra.42.fr/oauth/token", data={'grant_type': 'client_credentials', 'client_id': uid, 'client_secret': secret})
r.raise_for_status()
access_token = r.text[17:81]

url = 'https://api.intra.42.fr/v2/campus/7/locations?access_token=%s&per_page=100&filter[active]=true&page=' % (access_token)

locations = []
x = 1
page = 1
while x:
	with contextlib.closing(urllib2.urlopen(url + "&page=" + str(page))) as x:
		result = json.load(x)
		if not result:
			x = 0
		locations += result
	page += 1

filename = sys.argv[1]
if os.path.isfile(filename):
	with open(sys.argv[1], 'r') as f:
		names = f.readlines()

	for name in names:
		found = 0
		name = name.rstrip()
		for l in locations:
			if l['user']['login'] == name:
				found = 1;
				print "%s is at %s" % (name, l['host'])
		if not found:
			print "%s not active in cluster" % (name)
else:
	print "USAGE: python %s {file}" % (sys.argv[0])
