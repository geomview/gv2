#-*-perl-*-

#
# Perl script to build a global browse file (./MsGv.bsc)
#

$| = 1;

@files = ();

sub makefilelist {
    local($dir) = @_;
    local($_);
    foreach $_ (<$dir/*.*>) {
        if (! -d $_) {
            if (  /^.*\.sbr$/ ) {
                $files[$#files+1] = $_;
            }
        } else {
	    &makefilelist($_);
        }
    }
}

&makefilelist("Common");
&makefilelist("Ms");

open(OUT, ">bscmake.cmd");
print OUT "/v /o MsGv.bsc\n";
foreach $file (@files) {
    print OUT "$file\n";
}
close(OUT);

# This assumes that both
#        C:\Program Files\DevStudio\Vc\bin
#   and  C:\Program Files\DevStudio\SharedIDE\bin
# are on the PATH:
system("bscmake \@bscmake.cmd");

&Exit("Hit <Return> to terminate...");

sub Exit {
    local($msg) = @_;
    printf("%s\n", $msg);
    local($_);
    $_ = <STDIN>;
    exit;
}


