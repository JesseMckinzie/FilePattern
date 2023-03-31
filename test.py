import filepattern as fp
import re
import os
#pattern = r'\{(\w+):(\w+(?:\+)?)\}'

def rename(fp: fp.FilePattern, current_filepattern: str, new_filepattern: str, string_renaming: dict={}):
    pattern = r'\{(\w+):(\w+(?:\+)?)\}'

    current_matches = re.findall(pattern, current_filepattern)
    new_matches = re.findall(pattern, new_filepattern)

    current_dict = {}
    for tup in current_matches:
        current_dict[tup[0]] = tup[1]

    new_dict = {}
    for tup in new_matches:
        new_dict[tup[0]] = tup[1]

    
    for file in fp():
        vars = file[0]
        path = file[1]
        new_values = {}
        for var in vars:
            if var not in current_dict.keys():
                raise ValueError("Variable not in current filepattern: " + var)

            value = vars[var]
            if (isinstance(value, int)):
                current_length = len(str(value))
                new_length = len(new_dict[var])

                zero_length = new_length - current_length 
                if (zero_length < 0):
                    raise ValueError('New variable length too short for variable ' + var)

                new_value = str(value).zfill(new_length)
                new_values[var] = new_value
            else:
                if (string_renaming):
                    new_value = string_renaming[value]
                    new_values[var] = new_value
                else:
                    raise ValueError('Must provide a dictionary for renaming strings')

        print(new_values)
        old_file_name = path.name
        new_file_name = path.name
        dir_name = os.path.dirname(path)

        



       # new_filepattern = new_filepattern.format(**string_to_numbers)
        #new_path = path.with_name(new_filepattern)
        #path.rename(new_path)


'''
def rename(fp: fp.FilePattern, current_filepattern: str, new_filepattern: str, string_to_numbers: dict={}):

    #pattern = r'\{(\w+):(\w+(?:\+)?)\}'
    pattern = r'(\{(\w+):(\w+(?:\+)?)}|[^{}]+)'

    current_matches = re.findall(pattern, current_filepattern)

    new_matches = re.findall(pattern, new_filepattern)

    current_dict = {}

    for tup in current_matches:
        current_dict[tup[0]] = tup[1]

    new_dict = {}

    for tup in new_matches:
        new_dict[tup[0]] = tup[1]

    print(current_dict)
    print(new_dict)

    for file in fp():
        print(file[0])
        print(file[1])

        vars = file[0]
        path = file[1]

        for var in vars:
            
            if var not in current_dict.keys():
                raise ValueError("Variable not in current filepattern: " + var)
        
            value = vars[var]
          
            if (isinstance(value, int)):
                current_length = len(str(value))
                new_length = len(new_dict[var])

                zero_length = new_length - current_length 

                if (zero_length < 0):
                    raise ValueError('New variable length too short for variable ' + var)
                
                new_value = str(value)
                new_value = new_value.zfill(new_length)

'''

'''
def rename(path, old_pattern, new_pattern):
   # Create a FilePattern object for the old pattern
    old_pat = fp.FilePattern(path, old_pattern)
    
    # Loop through each matching file
    for values, files in old_pat():
        # Replace the variables in the new pattern with the extracted values
        new_name = new_pattern.format(c=values['c'], x=values['x'], y=values['y'])
        
        # Get the old file name
        old_name = str(files[0])
        
        # Rename the file
        os.rename(old_name, os.path.join(path, new_name))
'''



path = '/Users/mckinziejr/Documents/GitHub/FilePattern/data'

pattern = 'img_x{x:dd}_y{y:dd}_{c:c+}.tif'

pat = fp.FilePattern(path, pattern)

new_pattern = 'newdata_x{x:ddd}_y{y:ddd}_c{c:ddd}.tif'

channel_to_nums = {'DAPI': '001', 'GFP': '002', 'TXRED': '003'}

rename(pat, pattern, new_pattern, channel_to_nums)

#for file in pat():
#    print(file)



    