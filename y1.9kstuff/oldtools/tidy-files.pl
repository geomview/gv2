$| = 1;

sub tidy {
    local($dir) = @_;
    local($_);
    foreach $_ (<$dir/*.*>) {
	if (! -d $_) {
	    if ( /.*~/ || /#*#/ ) {
		print ("deleting file $_\n");
		unlink($_);
	    }
	} else {
	    &tidy($_);
	}
    }
}

&tidy(".");

&Exit("Hit <Return> to terminate...");

sub Exit {
    local($msg) = @_;
    printf("%s\n", $msg);
    local($_);
    $_ = <STDIN>;
    exit;
}
