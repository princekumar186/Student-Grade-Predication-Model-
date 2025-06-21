import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
import ssl

# Define your email credentials and SMTP server information
sender_email = "your_email@gmail.com"
receiver_email = "recipient_email@example.com"
password = "your_email_password"

# Email content
subject = "Custom Email Subject"
body = """
Hello,

This is a custom email message.

Best regards,
Your Name
"""

# Create the email message
message = MIMEMultipart()
message["From"] = sender_email
message["To"] = receiver_email
message["Subject"] = subject

# Attach the body to the email
message.attach(MIMEText(body, "plain"))

# Establish a secure SSL connection with the Gmail server
context = ssl.create_default_context()

try:
    # Connect to the Gmail SMTP server
    with smtplib.SMTP_SSL("smtp.gmail.com", 465, context=context) as server:
        # Login to the email account
        server.login(sender_email, password)
        
        # Send the email
        server.sendmail(sender_email, receiver_email, message.as_string())
        print("Email sent successfully!")
except Exception as e:
    print(f"Error sending email: {e}")
