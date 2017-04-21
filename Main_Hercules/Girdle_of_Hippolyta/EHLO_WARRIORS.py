#!/usr/bin/env python

import smtplib

from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText

# fromaddr == my email address
# toaddrs == recipient's email address
fromaddr = "heracles.gatekeeper@gmail.com"
toaddrs = "phillyeagles60@gmail.com"

# Create message container - the correct MIME type is multipart/alternative.
msg = MIMEMultipart('alternative')
msg['Subject'] = "Link"
msg['From'] = fromaddr
msg['To'] = toaddrs

# Create the body of the message (a plain-text and an HTML version).
text = "Hi!\nHow are you?\nHere is the link you wanted:\nhttps://www.python.org"
html = """\
<html>
  <head>
  	<style>
	  body {
	    background-image: url("https://static.vecteezy.com/system/resources/previews/000/139/204/original/hercules-statue-vector.jpg");
	    background-position: cover;
	    background-repeat: none;
	  }
	  .intro, .subject {
	    text-align: center;
	    vertical-align: middle;
	  }
	  .intro {
		font-size: 23px;
		color: #B20000;
	  }
	  .subject {
		font-size: 16px;
		color: #B20000;
	  }
	  .girdle {
		display: block;
		margin: 0 auto;
		height: 200px;
		width: 200px;
	  }
	</style>
  </head>
  <body>
	<p class='intro' style>To my fellow brethren,</p>
	<p class='subject'>
		  I call upon you all to help me acquire the Girdle of Hippolyta. The   Amazons will prove no match to us and will be defeated with ease. We   leave at the crack of dawn tonight.
	</p>
	<img class='girdle' src="http://mg1.duckdns.org/wiki/images/e/e0/HippolytaSSP.png"/>
  </body>
</html>
"""

# Record the MIME types of both parts - text/plain and text/html.
part1 = MIMEText(text, 'plain')
part2 = MIMEText(html, 'html')

# Attach parts into message container.
# According to RFC 2046, the last part of a multipart message, in this case
# the HTML message, is best and preferred.
msg.attach(part1)
msg.attach(part2)

# connect to gmail
username = 'heracles.gatekeeper@gmail.com'
password = 'MountOlympus'
# send the message via gmail
server = smtplib.SMTP('smtp.gmail.com:587')
server.ehlo()
server.starttls()
# login to google and send message
server.login(username,password)
server.sendmail(fromaddr, toaddrs, msg.as_string())
# and message to send - here it is sent as one string.
server.quit()