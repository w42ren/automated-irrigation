from flask import Flask, render_template,make_response
import requests
requests.packages.urllib3.disable_warnings()

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route("/api/v2/test_response")
def users():
    headers = {"Content-Type": "application/json"}
    return make_response(
        'Test worked!',
        200,
 #       headers= {"X-Content-Type-Options": "nosniff"}
    )
@app.route("/api/v2/send_response")
def senders():
    api_url = "https://192.168.0.5/arduino/digital/5"

    headers = { "Accept": "text/html",
            "Content-type":"text/html"
          }

    resp = requests.get(api_url, headers=headers, verify=False)
    return make_response(
		resp.text,
		200,
     		)
@app.route('/foo', methods=['GET', 'POST'])

def foo(x=None, y=None):
    api_url = "https://192.168.0.5/arduino/digital/4"
    headers = { "Accept": "text/html",
            "Content-type":"text/html"
          }
    resp = requests.get(api_url, headers=headers, verify=False)
    return make_response(
                resp.text,
                200,
                )
    pass
@app.route('/bar', methods=['GET', 'POST'])

def bar(x=None, y=None):
    api_url = "https://192.168.0.5/arduino/digital/5"
    headers = { "Accept": "text/html",
            "Content-type":"text/html"
          }
    resp = requests.get(api_url, headers=headers, verify=False)
    return make_response(
                resp.text,
                200,
                )
    pass

app.run(host='0.0.0.0', port=80)
