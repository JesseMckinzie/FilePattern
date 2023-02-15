import filepattern as fp
path = '/Users/jessemckinzie/Documents/GitHub/FilePattern/data'

#pattern = fp.infer_pattern(path)

#print(pattern)

pat = fp.FilePattern(path, 'x{x:d}_y{y:d}.tif')

#pat = fp.FilePattern(path, 'x{x}_y{y}.tif')

for file in pat(group_by=[]):
    print(file)
    print('------')
    