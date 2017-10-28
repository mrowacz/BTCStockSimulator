## Simulation Data

Download data from https://www.kaggle.com/qalfredo/bitcoin-prices-coinbase-usd

## Docker requirements

1. create directory data in this repo
2. run mongodb container

    ```bash
    sudo docker run -d -p 27017:27017 -v ${PWD}/data:/data/db mongo
    ```
3. use scripts from python dir