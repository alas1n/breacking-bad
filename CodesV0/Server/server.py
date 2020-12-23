from flask import Flask, jsonify, request, render_template

app = Flask(__name__)

number = 0

# POST - used to receive data
# GET - used to send data back only

# POST /store data: {name}
# "http://127.0.0.1:5000/store/some_name"

# GET /send
@app.route('/send',methods=["GET"])
def send_data():
    global number
    if number > 5 :
        number = 0
    else:
        number = number + 1
    return jsonify(number)


# GET /receive
@app.route('/receive',methods=["GET"])
def receive_data():
    return jsonify(number)


app.run(port=5002)