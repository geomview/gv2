chdir("..");

$| = 1;

$ARCHIVE = "Geomview-src";

@files = ();

sub makefilelist {
    local($dir) = @_;
    local($_);
    foreach $_ (<$dir/*.*>) {
	if (!/old/) {
	    if (! -d $_) {
		if (/\.cpp$/	||
		    /\.h$/	||
		    /\.c$/ ) {
		    $files[$#files+1] = $_;
		}
	    } else {
		&makefilelist($_);
	    }
	}
    }
}

&makefilelist("Geomview");

$ListFileName = "LISTFILE.tmp";
open(LISTFILE, ">$ListFileName");
foreach $file (@files) {
    print LISTFILE "$file\n";
}
close(LISTFILE);

$code = system("tar -c -v -f $ARCHIVE.tar -T $ListFileName");
if ($code != 0) {
    &Exit("there were errors in executing tar; are some files open?\n");
}
$code = system("gzip $ARCHIVE.tar");
if ($code != 0) {
    &Exit("there were errors in executing gzip\n");
}

printf("\nCreated file $ARCHIVE.tar.gz\n");

unlink("$ListFileName");

&Exit("Hit <Return> to terminate...");

sub Exit {
    local($msg) = @_;
    printf("%s\n", $msg);
    local($_);
    $_ = <STDIN>;
    exit;
}


