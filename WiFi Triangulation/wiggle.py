import requests
import webbrowser
import json
import sys


import numpy as np
from scipy.spatial.distance import cdist, euclidean

def geometric_median(X, eps=1e-5):
    y = np.mean(X, 0)

    while True:
        D = cdist(X, [y])
        nonzeros = (D != 0)[:, 0]

        Dinv = 1 / D[nonzeros]
        Dinvs = np.sum(Dinv)
        W = Dinv / Dinvs
        T = np.sum(W * X[nonzeros], 0)

        num_zeros = len(X) - np.sum(nonzeros)
        if num_zeros == 0:
            y1 = T
        elif num_zeros == len(X):
            return y
        else:
            R = (T - y) * Dinvs
            r = np.linalg.norm(R)
            rinv = 0 if r == 0 else num_zeros/r
            y1 = max(0, 1-rinv)*T + min(1, rinv)*y

        if euclidean(y, y1) < eps:
            return y1

        y = y1

def main():
    '''
        Sends a request for each BSSID given as Parameter. The responses are saved in a jsons
        folder. The latitude and longitude of all given BSSIDs is averaged and the resulting
        location is opend in google maps.
    '''
    if len(sys.argv) > 1:
        BSSIDs = sys.argv[1:]
    else:
        print("Usage: python3 wiggle.py BSSID1 BSSID2 ...")
        exit()

    positions = []

    for BSSID in BSSIDs:
        headers = {
            'Accept': 'application/json',
        }

        params = (
            ('netid', BSSID),
            ('type', 'WIFI'),
        )

        auth = (
            'AIDf0f1887395c7c6d0a4cb9b1d55ac4670', '77ff99adcd69a3b061a599041c548ec0'
        )

        response = requests.get('https://api.wigle.net/api/v2/network/detail',
                                headers=headers,
                                params=params,
                                auth=auth)

        data = response.json()
        if 'results' in data:
            with open(f'./jsons/{BSSID}_result.json', 'w+', encoding='utf-8') as file:
                json.dump(data, file, ensure_ascii=False, indent=4)
            lat = data['results'][0]['trilat']
            long = data['results'][0]['trilong']
            positions.append([lat, long])
            print(f'https://www.google.com/maps/place/{lat},{long}')

        else:
            print(data)

    median_position = geometric_median(np.array(positions))

    webbrowser.open(f'https://www.google.com/maps/place/{median_position[0]},{median_position[1]}')

    return median_position


if __name__ == "__main__":
    print(main())
