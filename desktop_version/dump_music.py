import re
import struct

HEADER_COUNT = 128

with open("vvvvvvmusic.vvv", "rb") as blob:
	headers = []
	for i in range(HEADER_COUNT):
		header = struct.unpack("<48s2iB3x", blob.read(60))
		if header[3] == 1:
			headers.append((''.join(header[0].decode("utf-8").split("\x00")), header[2]))

	for (name, size) in headers:
		ogg = blob.read(size)
		filepath = re.sub("^data\\/music", "music", name)
		with open(filepath, "wb") as out:
			out.write(ogg)