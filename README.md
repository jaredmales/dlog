A system for managing a digital log with git.

## Configuration

Place a configuration file in the `$(HOME)/.dlog/dlog.conf`.  Its contents should be something like:
```
user-name=email@domain.org
path=/home/username/.dlog
editor=vi
```

## Apache Setup

Enable a firewall on your machine.  On ubuntu do
```
$ sudo ufw enable
$ sudo ufw status
```

```
$ sudo apt install apache2
$ sudo systemctl status apache2
```

Edit `/etc/hosts` to contain the entry
```
127.0.0.1  dlog
```

```
$ sudo mkdir /var/www/dlog
$ sudo chown jrmales:jrmales /var/www/dlog
$ sudo chmod -R 755 /var/www/dlog
$ vi /var/www/dlog/index.html
```
And make it say:
```
<html>
    <head>
        <title>Welcome to dlog</title>
    </head>
    <body>
        <h1>Success!  The dlog virtual host is working!</h1>
    </body>
</html>
```

```
$ sudo vi /etc/apache2/sites-available/dlog.conf
```
and make it say:
```
<VirtualHost *:80>
    ServerAdmin webmaster@localhost
    ServerName dlog
    ServerAlias dlog
    DocumentRoot /var/www/dlog
    ErrorLog ${APACHE_LOG_DIR}/error.log
    CustomLog ${APACHE_LOG_DIR}/access.log combined
</VirtualHost>
```

```
$ sudo a2ensite dlog.conf
$ sudo apache2ctl configtest
```
You can ignore a fully qualified domain name warning about 127.0.0.1.  If it otherwise says "Syntax OK", then
```
$ systemctl reload apache2
```
Now visiting `http://dlog` from your favorite browser should show a message about dlog.

### CGI Setup
```
$ sudo a2enmod cgid
$ sudo systemctl restart apache2
$ sudo vi /etc/apache2/conf-available/cgi-enabled.conf
```

```
<Directory "/var/www/dlog">
    Options +ExecCGI
    AddHandler cgi-script .cgi .pl
</Directory>
```

```
$ sudo a2enconf cgi-enabled
$ systemctl reload apache2
$ sudo cp ~/Source/c/mxApps/dlog/dlogquery /var/www/dlog/index.cgi
$ sudo chmod 705 /var/www/dlog/index.cgi
$ sudo rm /var/www/dlog/index.html
```

