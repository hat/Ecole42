# from flask import Flask
# from flask_mail import Mail, Message

# app =Flask(__name__)
# mail=Mail(app)

# app.config['MAIL_SERVER']='smtp.gmail.com'
# app.config['MAIL_PORT'] = 465
# app.config['MAIL_USERNAME'] = 'heracles.gatekeeper@gmail.com'
# app.config['MAIL_PASSWORD'] = 'MountOlympus'
# app.config['MAIL_USE_TLS'] = False
# app.config['MAIL_USE_SSL'] = True
# mail = Mail(app)

# @app.route("/")
# def index():
#    msg = Message('Hello', sender = 'heracles.gatekeeper@gmail.com', recipients = ['id1@gmail.com'])
#    msg.body = "Hello Flask message sent from Flask-Mail"
#    mail.send(msg)
#    return "Sent"

# if __name__ == '__main__':
#    app.run(debug = True)


import os
from flask import Flask, render_template, redirect
from flask_script import Command
from flask_mail import Mail, Message
from flask_wtf import Form
from wtforms import StringField, SubmitField


app = Flask(__name__)

app.config['MAIL_SERVER'] = 'smtp.googlemail.com'
app.config['MAIL_PORT'] = 587
app.config['MAIL_USE_TLS'] = True
app.config['MAIL_USERNAME'] = 'heracles.gatekeeper@gmail.com'
app.config['MAIL_PASSWORD'] = 'MountOlympus'
app.config['DEFAULT_MAIL_SUBJECT'] = '[Politburo Voting Results]'
app.config['DEFAULT_MAIL_SENDER'] = 'Admin <heracles.gatekeeper@gmail.com>'
app.config['SECRET_KEY'] = 'random_string'
app.config['DEFAULT_ADMIN'] = 'Admin <phillyeagles60@gmail.com>'

mail = Mail(app)


class PolitburoForm(Form):
    name = StringField('GET TROOPS')
    submit = SubmitField('Submit')


def send_email(to, subject, template, **kwargs):
    msg = Message(app.config['DEFAULT_MAIL_SUBJECT'] + ' ' + subject,
        sender=app.config['DEFAULT_MAIL_SENDER'], recipients=[to])
    msg.html = render_template(template + '.html', **kwargs)
    mail.send(msg)


@app.route('/', methods=('GET', 'POST'))
def submit():
    form = PolitburoForm()
    if form.validate_on_submit():
        name = form.name.data
        send_email(app.config['DEFAULT_ADMIN'], 'Button clicked', 'mail/favorite', name=name)
        return redirect('/')
    return render_template('index.html', form=form)


if __name__ == '__main__':
    app.run(debug=True)