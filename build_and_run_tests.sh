#!/bin/bash

function build_and_run_tests() {
  pushd build
  rm -rf coverage/harvest_sweeper_unit_test sources bin
  find . -type f -name "*.gcda" -exec rm {} \;
  cmake ../
  make -j`nproc`

  pushd coverage

  cat <<EOF > test.json
{
  "root" : [
    {
      "cp": "/usr/bin/cp",
      "ls": "/usr/bin/ls",
      "mkfs": "/usr/sbin/mkfs",
      "wget": "/usr/sbin/wget",
      "file": "/usr/bin/file",
      "more": "/usr/bin/more",
      "grep": "/usr/bin/grep",
      "cat": "/usr/bin/cat",
      "chmod": "/usr/bin/chmod",
      "chown": "/usr/bin/chown"
    }
  ]
}
EOF

  cat <<EOF > broken.json
{
  "root" : [
    {
      "cp": "/usr/bin/cp",
      "ls": "/usr/bin/ls",
      "mkfs": "/usr/sbin/mkfs"
      "wget": "/usr/sbin/wget"
    }
  ]
  "broken": [
    {
      c"p: /usr/bin/cp"
    }
  ]
}
EOF

  touch A.json
  touch a.json

  popd

  make coverage
  popd
}


if [ ! -e 'build' ]; then
  mkdir -v build
fi

build_and_run_tests

exit 0
