import unittest, json
from pathlib import Path
import filepattern2 as fp

"""
NOTE: Run the file "generate_data.py" in /tests and in "examples" before running this file.
"""

class InferenceTest(unittest.TestCase):
    """Verify VERSION is correct """

    json_path = Path(__file__).parent.parent.joinpath("plugin.json")
    
    def setUp(self):
        
        with open(Path(__file__).with_name('test_infer_pattern_data.json'),'r') as fr:
            
            self.data = json.load(fr)
            
    def test_numeric_fixed_width(self):
        
        pattern = fp.infer_pattern(files=self.data['robot'])

        self.assertEqual(pattern,'00{r:d}0{t:dd}-{c:d}-00100100{z:d}.tif')

    def test_alphanumeric_fixed_width(self):
        
        pattern = fp.infer_pattern(files=self.data['brain'])

        self.assertEqual(pattern,'S1_R{r:d}_C1-C11_A1_y0{t:dd}_x0{c:dd}_c0{z:dd}.ome.tif')
        
    def test_alphanumeric_variable_width(self):
        
        pattern = fp.infer_pattern(files=self.data['variable'])

        self.assertEqual(pattern,'S1_R{r:d}_C1-C11_A1_y{t:d+}_x{c:d+}_c{z:d+}.ome.tif')

    def test_alphanumeric_channel_variable_width(self):
        
        pattern = fp.infer_pattern(files=self.data['channel'])

        self.assertEqual(pattern,'img_r00{r:d}_c00{t:d}_{c:c+}.tif')
    
    def test_variable_naming(self):
        pattern = fp.infer_pattern(files=self.data['channel'], variables='xyz')
        
        self.assertEqual(pattern,'img_r00{x:d}_c00{y:d}_{z:c+}.tif')

    def test_alphanumeric_both_variable_width(self):

        pattern = fp.infer_pattern(files=self.data['both'])

        self.assertEqual(pattern, '{r:cccccc}_{t:d+}_{c:c+}.ome.tif')
    
    def test_invalid_input(self):
        with self.assertRaises(RuntimeError):
            pattern = fp.infer_pattern(files=self.data['invalid'])

class ExternalInferenceTest(unittest.TestCase):

    path = 'tests/test_data/data'
    def test_fp_single_block(self):
        pattern = fp.infer_pattern(path=self.path, block_size='1 GB')
        
        self.assertEqual(pattern, 'img_r00{r:d}_c00{t:d}_{c:c+}.tif')
        
    def test_fp_multiple_block(self):
        pattern = fp.infer_pattern(path=self.path, block_size='1 MB')
        
        self.assertEqual(pattern, 'img_r00{r:d}_c00{t:d}_{c:c+}.tif')
        
    def test_sp_single_block(self):
        path = 'tests/test_data/sp_data.txt'
        pattern = fp.infer_pattern(path=path, block_size='1 GB')
        
        self.assertEqual(pattern, 'img_r00{r:d}_c00{t:d}_{c:c+}.tif')
        
    def test_sp_multi_block(self):
        path = 'tests/test_data/sp_data.txt'
        pattern = fp.infer_pattern(path=path, block_size='900 B')
        
        self.assertEqual(pattern, 'img_r00{r:d}_c00{t:d}_{c:c+}.tif')
    
    def test_vp_single_block(self):
        path = 'tests/test_vectorpattern_data.txt'
        pattern = fp.infer_pattern(path=path, block_size='1 GB')
        
        self.assertEqual(pattern, 'x{r:dd}_y{t:dd}_wx{c:d}_wy{z:d}_c1.ome.tif')
                
    def test_vp_multi_block(self):
        path = 'tests/test_vectorpattern_data.txt'
        pattern = fp.infer_pattern(path=path, block_size='1 KB')
        
        self.assertEqual(pattern, 'x{r:dd}_y{t:dd}_wx{c:d}_wy{z:d}_c1.ome.tif')


if __name__=="__main__":

    unittest.main()