import os
import codecs

out = open('out.txt', 'w')
for root, dirs, fns in os.walk('.'):
    for fn in fns:
        _, ext = os.path.splitext(fn)
        if ext not in ['.h', '.c', '.hpp', '.cpp'] or fn == 'output.py':
            continue
        out.write('<<<<<<<<' + os.path.join(root, fn) + '>>>>>>>>\r\n')
        with codecs.open(os.path.join(root, fn), 'r', encoding='gbk') as f:
            str = f.read()
            str = str.replace('\r', '')
            out.write(str)
        out.write('\n\n\n\n')
out.close()