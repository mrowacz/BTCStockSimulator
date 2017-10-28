import datetime
from pymongo import MongoClient
from numpy import diff
import matplotlib.pyplot as plt

client = MongoClient('localhost', 27017)
db = client['btc-stock-db']
btc_collection = db['btc-usd']

stock = []
dt = []
for post in btc_collection.find():
    stock.append(float(post["price"]))
    dt.append(post["date"])

print "Start date: " + str(dt[0])
print "End date: " + str(dt[len(dt)-1])

# calc diverative
dst = diff(stock)
print "Maximal growth: " + str(max(dst))
print "Maximal drop: " + str(min(dst))

plt.plot(stock)
plt.ylabel('BTC stock price [USD]')
plt.show()