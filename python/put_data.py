import datetime
from tqdm import *
from pymongo import MongoClient

client = MongoClient('localhost', 27017)
db = client['btc-stock-db']
btc_collection = db['btc-usd']
btc_collection.drop()

with open("bit_pr.csv") as f:
    lines = f.readlines()
    iterlines = iter(lines)
    next(iterlines)
    pbar = tqdm(total=len(lines)-1)
    for line in iterlines:
        [empty, timestamp, price] = line.split(",")
        post = {
            "date": datetime.datetime.fromtimestamp(float(timestamp)),
            "price": price.rstrip()
        }
        btc_collection.insert_one(post)
        pbar.update(1)
