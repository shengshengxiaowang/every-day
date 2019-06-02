create database BK04173028;

create table Book28
(
	BookID char(3) primary key,
	BookName varchar(20),
	BookType varchar(10),
	Press varchar(10),
	Author varchar(20),
	Price money,
	PubDate time
)

create table Reader28
(
	ReaderID char(2)primary key,
	ReaderName varchar(20),
	Dept varchar(10),
	sex char(2),
	Address varchar(20),
	Phone char(12)
)

create table Borrow28
(
	BookID char(3) ,
	ReaderId char(2),
	BorDate time,
	primary key(BookID,ReaderID),
    foreign key(BookID) references Book28(BookID),
    foreign key(ReaderID) references Reader28(ReaderID)
)
insert into Book28 values('001','shujuku','jisuanji','youdian','mengcaixia','33','1999-01-01');
insert into Book28 values('002','shu','jisuanji','youdian','mengcaixia','33','1999-01-01');
insert into Book28 values('003','shuku','jisuanji','youdian','mengcaixia','33','1999-01-01');


insert into Book28 values('01','laixin','asf','nv','sgsd','123');
insert into Book28 values('02','lai','asf','nv','sgsd','42');
insert into Book28 values('03','lain','asf','nv','sgsd','123453');


select *
from Book28
where BookType='jisuanji';

select *
from Book28
where Author='mengcaixia';

select *
from Book28,Borrow28
where BorDate between 2018-01-01 and 2018-12-31;


select Borrow28.BookID,BookName,BorDate
from Book28,Borrow28
where in (select Readername='laixin' from Reader28);

select *
from Book28
where in (select * from Borrow28 where BorDate=null)


update Reader28
set Address='dsads'
where Readername='asdgag';


delete
from Reader28
where Readername='laixin';
