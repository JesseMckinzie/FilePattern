import filepattern2 as fp 
import filepattern as fpo
import pprint

path = '/Users/jessemckinzie/Desktop/data/int'

pattern = 'p{p:d}_y{y:d}_r{r:d}_c{c:d}.ome.tif'


f = fp.FilePattern(path, pattern)

for file in f():
    pprint.pprint(file)
    