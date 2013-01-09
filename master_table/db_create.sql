create table `board` (`id` int primary key, `table` varchar(20), `type` int(4) default 1, `ipv4` varchar(16), `port` int(5) );

create table `competitor` (`id` int primary key, `name` varchar(150), `cats` int(6) , `wins` int, `loss` int, `ptaken` int, `pgiven` int);

create table `bout` (`id` int primary key, `table` int, `aka` int, `aou` int, `score` char(5) default '0:0', `cat1` char(3) default '0:0', `cat2` char(3) default '0:0');

create table `categories` (`type` int(6), `name` varchar(20));



