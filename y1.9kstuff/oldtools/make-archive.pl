chdir("..");

($sec,$min,$hour,$mday,$mon,
 $year,$wday,$yday,$isdst) = localtime(time());

$datestamp = sprintf("%02d.%02d.%02d-%02d.%02d.%02d",
		$year, $mon+1, $mday, $hour, $min, $sec);

$ARCHIVE_BASENAME = "Geomview-$datestamp";

$ARCHIVE="archives/$ARCHIVE_BASENAME";

$| = 1;

@files = ();

sub makefilelist {
    local($dir) = @_;
    local($_);
    foreach $_ (<$dir/*.*>) {
	if (! -d $_) {
	    if (  !/^.*~$/              &&
		  !/^#.*#$/             &&
		  !/^.*\.bsc$/          &&
		  !/\/lib\/[^\/]+$/     &&
		  !/\/bin\/[^\/]+$/     &&
		  !/\/Debug\/[^\/]+$/    ) {
		$files[$#files+1] = $_;
	    }
	} else {
	    &makefilelist($_);
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

# unlink("$ListFileName");

# append this archive name to NOTES.txt file
open(NOTES, ">>archives/NOTES.txt");
print(NOTES "\n$ARCHIVE_BASENAME.tar.gz\n");
close(NOTES);


&Exit("Hit <Return> to terminate...");

sub Exit {
    local($msg) = @_;
    printf("%s\n", $msg);
    local($_);
    $_ = <STDIN>;
    exit;
}


