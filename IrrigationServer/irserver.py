from flask import Flask, render_template,make_response,request
import requests
from requests.compat import urljoin
requests.packages.urllib3.disable_warnings()

app = Flask(__name__)

@app.route('/')
def index():
    btn4 = False
    btn5 = False
    api_url = "https://192.168.0.5/arduino/mode/4/output"
    headers = { "Accept": "text/html",
            "Content-type":"text/html"
          }
    resp = requests.get(api_url, headers=headers, verify=False)
    return render_template('buttons.html', btn=False)
    
@app.route('/foo', methods=['GET', 'POST'])
def foo(x=None, y=None):
    api_url = "https://192.168.0.5/arduino/digital/4/1"
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
    api_url = "https://192.168.0.5/arduino/digital/5/1"
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
    # btn = True 
    if request.method == 'POST':
        if request.form['pin4'] == 'off':
            btn4 = False
        elif request.form['pin4'] == 'on':
            btn4 = True
    if request.method == 'GET':
        if request.args['pin4'] == 'off':
            btn4 = False
        elif request.args['pin4'] == 'on':
            btn4 = True
    base_url = "https://192.168.0.5/arduino/digital/4/"
    if btn4 == True : state = '1'
    else : state= '0'
    api_url = urljoin(base_url,state)
    headers = { "Accept": "text/html",
            "Content-type":"text/html"
          }
    resp = requests.get(api_url, headers=headers, verify=False)

    return render_template('buttons.html', pin4 = btn4, response = resp)
    pass

@app.route('/toggle_pin_5', methods=['GET', 'POST'])
def toggle_pin_5 ():
    # btn = True
    if request.method == 'POST':
        if request.form['pin5'] == 'off':
            btn5 = False
        elif request.form['pin5'] == 'on':
            btn5 = True
    if request.method == 'GET':
        if request.args['pin5'] == 'off':
            btn5 = False
        elif request.args['pin5'] == 'on':
            btn5 = True
    base_url = "https://192.168.0.5/arduino/digital/5/"
    if btn5 == True : state = '1'
    else : state= '0'
    api_url = urljoin(base_url,state)
    headers = { "Accept": "text/html",
            "Content-type":"text/html"
          }
    resp = requests.get(api_url, headers=headers, verify=False)

    return render_template('buttons.html', pin5 = btn5, response = resp)
    pass

app.run(host='0.0.0.0', port=80)

