import filepattern2 as fp
path = "/Users/jessemckinzie/Desktop/data/int"
pat = fp.FilePattern(path, 'p{p:d}_y{y:d}_r{r:d}_c{c:d}.ome.tif')

for file in pat():
    print(file)

print("After Loop")
