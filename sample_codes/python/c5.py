import glob
import numpy as np
from natsort import natsorted

NumImg:int = 15

class PNM():
    def __init__(self, filename:str):
        self.fname = filename
        with open(filename,'rb') as f:
            header = f.readline()
            assert header[:2] in [b'P1', b'P2', b'P3', b'P4', b'P5', b'P6']
            tPPM = int(header[1])
            if tPPM%3 == 0: self.NumChannels = 3
            else: self.NumChannels = 1
            self.IsASCII = True
            if tPPM//3 > 0: self.IsASCII = False

            line = f.readline()
            if line[0] == '#':
                line = f.readline()
            (self.NumCols,self.NumRows) = [int(i) for i in line.split()]

            line = f.readline()
            if line[0] == '#':
                line = f.readline()
            self.NumDepth = int(line)
            print(f'***')
            print(f'{self.fname=}')
            print(f'{self.NumRows}x{self.NumCols}x{self.NumChannels}')
            print(f'{self.IsASCII=}')
            print(f'***')

    def read(self)->np.ndarray:
        with open(self.fname,'rb') as f:
            raster = list()
            for _ in range(self.NumRows):
                row = list()
                for _ in range(self.NumCols):
                    if self.NumChannels>0:
                        col = list()
                        for _ in range(self.NumChannels):
                            if self.IsASCII:
                                col.append(f.read(1))
                            low = ord(f.read(1))
                            if self.NumDepth > 255:
                                col.append(low + 255 * ord(f.read(1)))
                            else:
                                col.append(low)
                        row.append(col)
                    else:
                        low = ord(f.read(1))
                        if self.NumDepth > 255:
                            row.append(low + 255 * ord(f.read(1)))
                        else:
                            row.append(low)
                raster.append(row)
            x = np.array(raster)
            print(f'画像 {self.fname} の一番初めの画素のR値は{x[0,0,0]}です\n')
        return x

def load_features_inDirectory(DirPath:str, ImgExt:str='pgm',sorting=True)->np.ndarray:
    fnamelist = glob.glob(f'{DirPath}/*.{ImgExt}')
    fnamelist = natsorted(fnamelist)
    features = list()
    for fname in fnamelist:
        print(fname)
        im = PNM(fname)
        imdata = im.read()
        features.append(imdata)
    features = np.array(features)
    return features

def main():
    DirPath = 'datasets/MNIST/train2000/images'
    features = load_features_inDirectory(DirPath=DirPath)

if __name__ == '__main__':
    main()


