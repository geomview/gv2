$| = 1;

sub delpch {
    local($dir) = @_;
    local($_);
    foreach $_ (<$dir/*.*>) {
	if (! -d $_) {
	    if ( /\.pch$/ ) {
		print ("deleting file $_\n");
		unlink($_);
	    }
	} else {
	    &delpch($_);
	}
    }
}

&delpch("Common");
&delpch("Ms");

&Exit("Hit <Return> to terminate...");

sub Exit {
    local($msg) = @_;
    printf("%s\n", $msg);
    local($_);
    $_ = <STDIN>;
    exit;
}
