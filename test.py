import filepattern2 as fp
path = "/Users/jessemckinzie/Desktop/data/int"

#pattern = fp.infer_pattern(path=path, variables='', block_size='50 GB')


pat = fp.FilePattern(path, 'p{p:d}_y{y:d}_r{r:d}_c{c:d}.ome.tif')

for file in pat():
    print(file)
    