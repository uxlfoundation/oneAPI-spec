from os import walk
from os.path import join
import re

r = re.compile(r'\W+:name: (known-limitations|return-values|include-files|note|note-1|note-2|note-3|syntax|description|input-parameters|output-parameters|example)')

for root, dirs, files in walk("."):
    for file in files:
        if not file.endswith(".rst"):
            continue
        p = join(root, file)
        print(p)
        in_lines = open(p).readlines()
        l2 = in_lines[2]
        dup_label = '.. _%s:\n' % l2.rstrip()
        print('dup_label:', dup_label)
        with open(p, 'w') as fout:
            for line in in_lines:
                if r.match(line) or line == dup_label:
                    print('omitting:', line)
                else:
                    fout.write(line)
