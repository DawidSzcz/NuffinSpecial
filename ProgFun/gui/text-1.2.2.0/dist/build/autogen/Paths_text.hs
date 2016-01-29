module Paths_text (
    version,
    getBinDir, getLibDir, getDataDir, getLibexecDir,
    getDataFileName
  ) where

import qualified Control.Exception as Exception
import Data.Version (Version(..))
import System.Environment (getEnv)
import Prelude

catchIO :: IO a -> (Exception.IOException -> IO a) -> IO a
catchIO = Exception.catch


version :: Version
version = Version {versionBranch = [1,2,2,0], versionTags = []}
bindir, libdir, datadir, libexecdir :: FilePath

bindir     = "/home/kazek/.cabal/bin"
libdir     = "/home/kazek/.cabal/lib/text-1.2.2.0/ghc-7.6.3"
datadir    = "/home/kazek/.cabal/share/text-1.2.2.0"
libexecdir = "/home/kazek/.cabal/libexec"

getBinDir, getLibDir, getDataDir, getLibexecDir :: IO FilePath
getBinDir = catchIO (getEnv "text_bindir") (\_ -> return bindir)
getLibDir = catchIO (getEnv "text_libdir") (\_ -> return libdir)
getDataDir = catchIO (getEnv "text_datadir") (\_ -> return datadir)
getLibexecDir = catchIO (getEnv "text_libexecdir") (\_ -> return libexecdir)

getDataFileName :: FilePath -> IO FilePath
getDataFileName name = do
  dir <- getDataDir
  return (dir ++ "/" ++ name)
