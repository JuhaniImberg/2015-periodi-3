((c-mode . ((c-file-style . "java")
            ;( This makes me sad
            (flycheck-clang-include-path . ("../include/" .
                                            ("../" .
                                             ("../../lib/include/*" .
                                              ("../../lib/include" .
                                               ("../../include" .
                                                 ("../../include/*" . nil)))))))
            (c-doc-comment-style . "javadoc"))))
