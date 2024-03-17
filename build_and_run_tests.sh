#!/bin/bash

function build_and_run_tests() {
  pushd build
  rm -rf coverage/harvest_sweeper_unit_test sources
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
      "wget": "/usr/sbin/wget"
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
