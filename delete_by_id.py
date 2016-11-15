#!/usr/bin/python3

import pickle
import sys

class Photo():
    def __init__(self, file_id):
        self.voted_user = []
        self.rate = 0
        self.file_id = file_id

allPhoto = pickle.load(open('photos.txt', 'rb'))
pickle.dump(allPhoto, open('photos_backup.txt', 'wb'))
for i in range(1, len(sys.argv)):
	for j in range(0, len(allPhoto)):
		if allPhoto[j].file_id == sys.argv[i]:
			allPhoto.remove(j)	
pickle.dump(allPhoto, open('photos.txt', 'wb'))
