# -*- coding: utf-8 -*-
import os

defname = 'definitions.h'

if __name__ == "__main__":
    if os.path.exists(defname):
        os.remove(defname)

    dest = open(defname, 'w')

    dest.write('#ifndef P1_COMP_DEFINITIONS_H\n' +
            '#define P1_COMP_DEFINITIONS_H\n' +
            '\n')

    with open("reserved.txt") as f:
        content = f.readlines()

        i = 300
        for line in content:
            print('#define D_'+str(line.rstrip())+' '+str(i))
            dest.write('#define D_' + str(line.rstrip()) + ' ' + str(i) + '\n')
            i+=1

    dest.write('\n' +
            '#endif //P1_COMP_DEFINITIONS_H')