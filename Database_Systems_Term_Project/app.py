## Author: Şafak Özkan Pala 150210016
## BLG-317E Database Systems Term Project

from flask import Flask
from controller import index

app = Flask(__name__)
app.register_blueprint(index)

if __name__ == '__main__':
        app.run(debug=True)