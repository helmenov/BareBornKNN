import numpy as np

MySeed = 2023
SizeSeries = 10

def main()->None:
    rg = np.random.default_rng(MySeed)

    for _ in range(SizeSeries):
        print(f'{rg.uniform()}')

    with open('test.dat','w') as f:
        for _ in range(SizeSeries):
            f.write(f'{rg.uniform()}\n')

if __name__ == '__main__':
    main()
