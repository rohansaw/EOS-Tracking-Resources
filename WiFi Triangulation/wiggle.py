import requests
import webbrowser
import json
import sys


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

    latitude = []
    longitude = []

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
            latitude.append(lat)
            longitude.append(long)
            print(f'https://www.google.com/maps/place/{lat},{long}')

        else:
            print(data)

    latitude = sum(latitude) / len(latitude)
    longitude = sum(longitude) / len(longitude)

    webbrowser.open(f'https://www.google.com/maps/place/{latitude},{longitude}')


if __name__ == "__main__":
    main()
