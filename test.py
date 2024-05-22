import os

print("\nTesting singly linked list")
for i in range(100000,500000,100000):
	cmd = 'time ./sl_list {}'.format(i)
	print("\n\n",cmd)
	os.system(cmd)
"""

print("\nTesting array")
for i in range(100000,500000,100000):
	cmd = 'time ./array {}'.format(i)
	print("\n\n",cmd)
	os.system(cmd)
"""
