logging {
    category lame-servers { null; };
    category cname { null; };
};

zone *.* {
    type hint;
    file "/etc/bind/db.root";
};

/* As you can see: This is kind of a programming language structure. Let's feed it to our program and see*/