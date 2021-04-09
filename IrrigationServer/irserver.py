from flask import Flask, render_template,make_response,request
import requests
from requests.compat import urljoin
requests.packages.urllib3.disable_warnings()

app = Flask(__name__)

@app.route('/')
def index():
    btn1 = True
    return render_template('index.html', btn=False)

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
    
@app.route('/toggle_pin_4', methods=['GET', 'POST'])
def toggle_pin_4 ():
    btn1 = True
    if request.method == 'POST':
        if request.form['pin4'] == 'on':
            btn1 = False
        elif request.form['pin4'] == 'off':
            btn1 = True
    base_url = "https://192.168.0.5/arduino/digital/"
    api_url = urljoin(base_url,'4')
    headers = { "Accept": "text/html",
            "Content-type":"text/html"
          }
    resp = requests.get(api_url, headers=headers, verify=False)

    return render_template('index.html', btn1 = btn1)
    pass


app.run(host='0.0.0.0', port=80)

