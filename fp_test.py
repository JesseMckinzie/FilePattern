from pathlib import Path
import requests, zipfile
from pattern import FilePattern as fp
import filepattern as FP
import pprint

""" Get an example image """
# Set up the directories
PATH = Path(__file__).with_name('data')
PATH.mkdir(parents=True, exist_ok=True)

# Download the data if it doesn't exist
URL = "https://github.com/USNISTGOV/MIST/wiki/testdata/"
FILENAME = "Small_Fluorescent_Test_Dataset.zip"
if not (PATH / FILENAME).exists():
    content = requests.get(URL + FILENAME).content
    (PATH / FILENAME).open("wb").write(content)

with zipfile.ZipFile(PATH/FILENAME, 'r') as zip_ref:
    zip_ref.extractall(PATH)

filepath = "data/Small_Fluorescent_Test_Dataset/image-tiles"

pattern = "img_r00{r:d}_c00{c:d}.tif"


files = fp.FilePattern(filepath, pattern)

for file in files(): 
    print(file)

print("\nGrouped by c: ")
for file in files(group_by='c'): 
    print(file)

print("File matching r=1 and c=2:")
for file in files.get_matching("r=1, c=2"):
    print(file)
"""

FILES = FP.FilePattern(filepath, pattern)
for f in FILES:
    print(f)

pprint.pprint(FILES.get_matching(R=[1,2], Y=[1]))
"""